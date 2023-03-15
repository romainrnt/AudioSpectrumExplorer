/*******************************************/
/*                                         */
/*  AudioSpectrumExplorer Project          */
/*  File: <Exceptions.hpp>                 */
/*  Author: romainrnt                      */
/*                                         */
/*******************************************/

#pragma once
#include <exception>
#include <string>
#include <iostream>

class Error : public std::exception {
    public:
        Error(const std::string &msg) noexcept;
        ~Error();
        const char *what() const noexcept override { return _msg.data(); }
        void printError() noexcept;
    protected:
        std::string _msg;
};