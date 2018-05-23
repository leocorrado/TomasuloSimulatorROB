/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommonDataBus.cpp
 * Author: leo
 * 
 * Created on 20 de mayo de 2018, 21:09
 */

#include "CommonDataBus.h"

CommonDataBus::CommonDataBus() {
    name = TagsReprise::NON;
    available = true;
    result = 0.0;
}


CommonDataBus::~CommonDataBus() {
}

bool CommonDataBus::isAvailable()
{
    return available;
}

void CommonDataBus::setAvailable(bool avail)
{
    available = avail;
}

void CommonDataBus::setName (TagsReprise nam)
{
    name = nam;
}

void CommonDataBus::setResult(float res)
{
    result = res;
}

float CommonDataBus::getResult()
{
    return result;
}

TagsReprise CommonDataBus::getName()
{
    return name;
}