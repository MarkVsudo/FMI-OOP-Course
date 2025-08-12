//=== src/utils/Exception.h ===
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class CSVException : public std::exception
{
private:
  std::string message;

public:
  CSVException(const std::string &msg) : message(msg) {}
  const char *what() const noexcept override { return message.c_str(); }
};

class InvalidDataTypeException : public CSVException
{
public:
  InvalidDataTypeException(const std::string &msg) : CSVException("Invalid data type: " + msg) {}
};

class InvalidColumnException : public CSVException
{
public:
  InvalidColumnException(const std::string &msg) : CSVException("Invalid column: " + msg) {}
};

class FileException : public CSVException
{
public:
  FileException(const std::string &msg) : CSVException("File error: " + msg) {}
};

#endif