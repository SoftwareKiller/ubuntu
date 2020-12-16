#include "parser.h"
#include <map>
#include <functional>

//1. 以+开头的简单字符串Simple Strings；
//2. 以-开头的，为错误信息Errors；
//3. 以:开头的，为整数Integers；
//4. 以$开头的，表示长度+字符串内容的字符串，redis叫它Bulk Strings；
//5. 以*开头的，redis协议里面叫Arrays，表示一个数组，是上面多种元素的组合。
//   Arrays是可以嵌套的，相当于一个树状结构，前面四种格式都是叶子节点，Arrays是非叶子节点。

// set aaa bbb的协议如下：
// eg:*3\r\n$3\r\nset\r\n$3\r\naaa\r\n$3\r\nbbb\r\n

std::shared_ptr<ReplyItem> ReplyItem::CreateItem(char c)
{
    std::map<char, std::function<ReplyItem*()>> factory_func{
        {'*', [](){
                      return new ArrayItem;
                  }},
        {'+', [](){
                      return new SimpleString;
                  }},
        {'-', [](){
                      return new ErrorString;
                  }},
        {'$', [](){
                      return new BulkString;
                  }},
        {':', [](){
                      return new NumberItem;
                  }},
    };

    auto f = factory_func.find(c);
    if(f != factory_func.end())
        return std::shared_ptr<ReplyItem>(f->second());
    return nullptr;
}

ParseResult ArrayItem::Result(char c)
{
    //ArrayItem的状态机
    switch(status_)
    {
    case AI_STATUS::AI_LENGTH: //处理长度和碰到\r后发生状态转换，转换为AI_LF
        {
            if(c != '\r')
            {
                if(std::isdigit(c) || (c == '-' && count_.size() == 0))
                {
                    count_.push_back(c);
                }
                else
                {
                    return ParseResult::ERROR;
                }
            }
            else
            {
                item_count_ = std::stoi(count_);
                status_ = AI_LF;
            }
            return ParseResult::CONTINUE;
        }
        break;
    case AI_STATUS::AI_LF://处理换行，改变状态为处理子树
        {
            //最后一个换行符，改变状态机的状态，继续解析子树
            if(c != '\n')
            {
                return ParseResult::ERROR;
            }

            status_ = AI_STATUS::AI_SUB_HEADER;

            if(item_count_ <= 0)
                return ParseResult::FINISHED;

            return ParseResult::CONTINUE;

        }
        break;
    case AI_STATUS::AI_SUB_HEADER:
        {
            current_ = CreateItem(c);
            if(!current_)
                return ParseResult::ERROR;

            items_.push_back(current_);
            status_ = AI_STATUS::AI_SUB_CONTENT;
            return ParseResult::CONTINUE;
        }
        break;
    case AI_STATUS::AI_SUB_CONTENT:
        {
            ParseResult ret = current_->Result(c);
            if(ret == ParseResult::ERROR)
                return ParseResult::ERROR;
            if(ret == ParseResult::FINISHED)
            {
                if(static_cast<int32_t>(items_.size()) >= item_count_)
                    return ParseResult::FINISHED;
                status_ = AI_STATUS::AI_SUB_HEADER;
            }
            return ParseResult::CONTINUE;
        }
        break;
    default:
        break;
    }

    return ParseResult::ERROR;
}

ParseResult OneLineString::Result(char c)
{
    switch(status_)
    {
    case OLS_STATUS::OLS_PARSING:
        {
            if(c != '\r')
            {
                content_.push_back(c);
            }
            else
            {
                status_ = OLS_STATUS::OLS_LF;
            }
            return ParseResult::CONTINUE;
        }
        break;
    case OLS_STATUS::OLS_LF:
        {
            if(c == '\n')
            {
                return ParseResult::FINISHED;
            }
            return ParseResult::ERROR;
        }
        break;
    }

    return ParseResult::ERROR;
}

ParseResult BulkString::Result(char c)
{
    switch(status_)
    {
    case BULK_STATUS::BS_LENGTH:
        {
            if(std::isdigit(c) || c == '-')
            {
                length_line_.push_back(c);
            }
            else
            {
                status_ = BULK_STATUS::BS_LF;
            }
            return ParseResult::CONTINUE;
        }
        break;
    case BULK_STATUS::BS_LF:
        {
            if(c != '\n')
                return ParseResult::ERROR;

            length_ = std::stoi(length_line_);
            if(length_ <= 0)
                return ParseResult::FINISHED;

            status_ = BS_CONTENT;
            return ParseResult::CONTINUE;
        }
        break;
    case BULK_STATUS::BS_CONTENT:
        {
            if(c != '\r')
            {
                content_.push_back(c);
            }
            else
            {
                status_ = BULK_STATUS::BS_CONTENT_LF;
            }

            return ParseResult::CONTINUE;
        }
        break;
    case BULK_STATUS::BS_CONTENT_LF:
        {
            if(c != '\n')
            {
                return ParseResult::ERROR;
            }

            return ParseResult::FINISHED;
        }
        break;
    default:
        break;
    }

    return ParseResult::ERROR;
}

ParseResult NumberItem::Result(char c)
{
    ParseResult ret = OneLineString::Result(c);
    if(ret == ParseResult::FINISHED)
        number_ = std::stoi(content_);

    return ret;
}
