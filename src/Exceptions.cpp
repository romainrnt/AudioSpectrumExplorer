/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <Exceptions.cpp>                 */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#include "../include/Exceptions.hpp"

Error::Error(const std::string &msg) noexcept : _msg(msg)
{
    printError();
}

Error::~Error()
{}

void Error::printError() noexcept
{
    std::cerr << "Error: " << _msg << std::endl;
}