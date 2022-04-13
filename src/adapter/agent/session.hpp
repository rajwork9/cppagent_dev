
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

#include <boost/beast/core/error.hpp>

#include <memory>

#include "url_parser.hpp"

namespace mtconnect::adapter::agent {

  struct ResponseDocument;
  struct AgentHandler;
  class Session : public std::enable_shared_from_this<Session>
  {
  public:
    using Next = std::function<bool(boost::beast::error_code ec, const ResponseDocument &doc)>;

    virtual ~Session() {}
    virtual void connect() = 0;
    virtual bool isOpen() const = 0;
    virtual void stop() = 0;

    virtual bool makeRequest(const std::string &suffix, const UrlQuery &query, bool stream,
                             Next next) = 0;

    AgentHandler *m_handler = nullptr;
    std::string m_identity;
  };

}  // namespace mtconnect::adapter::agent
