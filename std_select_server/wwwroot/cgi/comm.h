#pragma once

#include<iostream>
#include<string.h>
#include<string>
#include<mysql.h>

using namespace std;

MYSQL* connectMysql();
void selectMysql(MYSQL* myfd, const string& name, const string& std_id);
void closeMysql(MYSQL* myfd);

