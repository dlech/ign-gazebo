/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef IGNITION_GAZEBO_GUI_ENTITYTREE_HH_
#define IGNITION_GAZEBO_GUI_ENTITYTREE_HH_

#include <map>
#include <memory>

#include <ignition/gazebo/gui/GuiSystem.hh>

namespace ignition
{
namespace gazebo
{
  class EntityTreePrivate;

  /// \brief TODO
  class TreeModel : public QStandardItemModel
  {
    Q_OBJECT

    /// \brief Constructor
    public: explicit TreeModel();

    /// \brief Destructor
    public: virtual ~TreeModel() = default;

    // Documentation inherited
    public: QHash<int, QByteArray> roleNames() const override;

    /// \brief Add an entity to the tree.
    /// \param[in] _entity Entity to be added
    /// \param[in] _entityName Name of entity to be added
    /// \param[in] _parentEntity Parent entity. By default, kNullEntity, which
    /// means it's a root entity.
    public slots: void AddEntity(unsigned int _entity,
        const QString &_entityName,
        unsigned int _parentEntity = kNullEntity);

    /// \brief Remove an entity from the tree.
    /// \param[in] _entity Entity to be removed
    public slots: void RemoveEntity(unsigned int _entity);

    public: Q_INVOKABLE QVariantMap Data(int row);

    /// \brief Keep track of which item corresponds to which entity.
    private: std::map<Entity, QStandardItem *> entityItems;
  };

  /// \brief Displays a tree view with all the entities in the world.
  ///
  /// ## Configuration
  /// None
  class EntityTree : public ignition::gazebo::GuiSystem
  {
    Q_OBJECT

    /// \brief Constructor
    public: EntityTree();

    /// \brief Destructor
    public: virtual ~EntityTree();

    // Documentation inherited
    public: virtual void LoadConfig(const tinyxml2::XMLElement *_pluginElem)
        override;

    // Documentation inherited
    public: virtual void Update(const UpdateInfo &,
                                EntityComponentManager &) override;

    /// \internal
    /// \brief Pointer to private data.
    private: std::unique_ptr<EntityTreePrivate> dataPtr;
  };
}
}

#endif
