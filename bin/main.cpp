/*
* MIT License
*
* Copyright (c) 2018 Derick Felix <derickfelix@zoho.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include <iostream>
#include <sstream>

#include "Scanner.h"
#include "Cwsq.h"
#include "Mindtct.h"
#include "Utils.h"

int main(int argc, const char *argv[])
{
  if (argc != 3)
  {
      std::cout << "usage: " << argv[0] << " <directory> <name> " << std::endl;
      return 1;
  }

  std::string directory = argv[1];
  std::string name = argv[2];

  if (Fcmb::InvalidDir(directory)) {
    std::cout << "Invalid directory name given!" << std::endl;
    return 2;
  }

  std::ostringstream oss;
  oss << directory << name << ".bmp";
  std::string bitmap = oss.str();

  LOG(bitmap)

  try
  {
      Scanner scanner(bitmap);
      scanner.ScanImage();
  }
  catch (const ScannerException& e)
  {
    std::cout << e.what() << std::endl;
    return 1;
  }

  Cwsq cwsq(bitmap);
  cwsq.Execute();

  Mindtct mindtct(directory + name);
  mindtct.Execute();

  oss.str(""); // clear ostream
  oss << directory << "bmp/" << name << ".bmp";
  Fcmb::MoveBinary(bitmap, oss.str());

  return 0;
}
