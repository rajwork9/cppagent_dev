//
// Copyright Copyright 2009-2021, AMT � The Association For Manufacturing Technology (�AMT�)
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

#include "reference.hpp"
#include "entity.hpp"
#include "utilities.hpp"

#include <list>
#include <map>
#include <optional>
#include <string>
#include <utility>

using namespace std;

namespace mtconnect
{
  using namespace entity;
  namespace device_model
  {
    
    FactoryPtr Reference::getFactory()
    {
      static FactoryPtr references;
      if (!references)
      {
        auto reference = make_shared<Factory>(
                                              Requirements {Requirement("idRef", false), Requirement("name", false)});
        
        references = make_shared<Factory>(Requirements {
          Requirement("ComponentRef", ENTITY, reference, 0, Requirement::Infinite),
          Requirement("DataItemRef", ENTITY, reference, 0, Requirement::Infinite)});
        
        references->registerMatchers();
        references->setMinListSize(1);
      }
      return references;
    }
    
    FactoryPtr Reference::getRoot()
    {
      static auto root = make_shared<Factory>(
                                              Requirements {Requirement("References", ENTITY_LIST, Reference::getFactory(), false)});
      
      return root;
    }
  }
}  // namespace mtconnect
