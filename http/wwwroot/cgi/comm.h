#pragma once

#include<iostream>
#include<string>
#include<mysql.h>

using namespace std;

MYSQL* connectMysql();
int insertMysql(MYSQL* myfd, const string& name, const string& gender, const string& hobby);
void selectMysql(MYSQL* myfd);
void closeMysql(MYSQL* myfd);

