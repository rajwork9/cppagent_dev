//
// Copyright Copyright 2009-2021, AMT – The Association For Manufacturing Technology (“AMT”)
// All rights reserved.
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#pragma once


#include <boost/beast/http/verb.hpp>
#include "parameter.hpp"

namespace mtconnect
{
  namespace http_server
  {
    class Session;
    using SessionPtr = std::shared_ptr<Session>;
    
    struct Request
    {
      boost::beast::http::verb m_verb;
      std::string m_body;
      std::string m_accepts;
      std::string m_contentType;
      std::string m_path;
      std::string m_foreignIp;
      uint16_t m_foreignPort;
      QueryMap m_query;
      ParameterMap m_parameters;
      SessionPtr m_session;
      
      template <typename T>
      std::optional<T> parameter(const std::string &s) const
      {
        auto v = m_parameters.find(s);
        if (v == m_parameters.end())
          return std::nullopt;
        else
          return std::get<T>(v->second);
      }
    };
    
    using RequestPtr = std::shared_ptr<Request>;
  }
}
