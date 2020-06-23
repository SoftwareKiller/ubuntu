#ifndef PARSER_H__
#define PARSER_H__

#include <memory>
#include <vector>
#include <string>

enum ParseResult{
    INIT,
    CONTINUE,
    FINISHED,
    ERROR
};

class ReplyItem
{
//interface
public:
    virtual std::string ToString() = 0;
    virtual ParseResult Result(char c) = 0;
    virtual ~ReplyItem()
    {
    }

    static std::shared_ptr<ReplyItem>  CreateItem(char c);
};

class ArrayItem : public ReplyItem
{
    enum AI_STATUS
    {
        AI_LENGTH,
        AI_LF,
        AI_SUB_HEADER,
        AI_SUB_CONTENT,
    };

public:
    ArrayItem() : status_(AI_STATUS::AI_LENGTH)
    {
    }

    std::string ToString() override
    {
        std::string result("[");
        for(size_t i = 0; i < items_.size(); ++i)
        {
            if(i > 0)
                result.append(", ");
            result.append(items_[i]->ToString());
            result.append("]");
        }
        return  result;
    }

    ParseResult Result(char c)override;

private:
    AI_STATUS status_;
    int32_t item_count_;
    std::string count_;
    std::shared_ptr<ReplyItem> current_;
    std::vector<std::shared_ptr<ReplyItem>> items_;
};

class OneLineString : public ReplyItem
{
    enum OLS_STATUS
    {
        OLS_PARSING,
        OLS_LF,
    };
public:
    std::string ToString() override
    {
        return content_;
    }

    ParseResult Result(char c) override;

protected:
    OLS_STATUS status_ = OLS_PARSING;
    std::string content_;
};

class SimpleString : public OneLineString
{
};

class ErrorString : public OneLineString
{
public:
    std::string ToString() override
    {
        return std::string("(error) ") + content_;
    }
};

class BulkString : public ReplyItem
{
    enum BULK_STATUS
    {
        BS_LENGTH,
        BS_LF,
        BS_CONTENT,
        BS_CONTENT_LF,
    };

public:
    std::string ToString() override
    {
        if(length_ == -1)
            return  "(nil)";

        return std::string("\"") + content_ + std::string("\"");
    }

    ParseResult Result(char c)override;

private:
    BULK_STATUS status_ = BULK_STATUS::BS_LENGTH;
    int length_ = 0;
    std::string length_line_;
    std::string content_;
};

class NumberItem : public OneLineString
{
public:
    std::string ToString() override
    {
        return std::string("(integer) ") + std::to_string(number_);
    }

    ParseResult Result(char c) override;

private:
    int number_ = -1;
};

#endif
