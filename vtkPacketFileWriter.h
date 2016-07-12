// Copyright 2013 Velodyne Acoustics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPacketFileWriter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPacketFileWriter -
// .SECTION Description
//

#ifndef __vtkPacketFileWriter_h
#define __vtkPacketFileWriter_h

#include <pcap.h>
#include <string>
#include <vector>
#include <boost/date_time.hpp>

using namespace boost::posix_time;

class vtkPacketFileWriter
{
public:

  // note these values are little endian, pcap wants the packet header and
  //data to be in the platform's native byte order, so assuming little endian.
  static const unsigned short LidarPacketHeader[21];

  static const unsigned short PositionPacketHeader[21];

  vtkPacketFileWriter();

  ~vtkPacketFileWriter();

  bool open(const std::string& filename);

  bool isOpen();

  void close();

  const std::string& GetLastError();

  const std::string& GetFileName();

  bool writePacket(const unsigned char* data, unsigned int dataLength, ptime t = ptime());

  bool writePacket(pcap_pkthdr* packetHeader, unsigned char* packetData);

protected:

  pcap_t* PCAPFile;
  pcap_dumper_t* PCAPDump;

  std::string FileName;
  std::string LastError;

  void ptimeToTimeval(ptime& t, struct timeval& tv) {
      tv.tv_usec = t.time_of_day().fractional_seconds();
      struct tm tm_ = to_tm(t);
      tv.tv_sec = mktime(&tm_);
  }
};

#endif