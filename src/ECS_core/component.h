#pragma once

namespace ecs {

// Total count of of unique Component<T>'s instanciated
extern int g_component_type_count;

// Use CRTP method to keep track of each unique component types ID
template <typename T>
class Component {
public:
  // On construction if an instance of Component<T> hasn't been created we give
  // it the next available ID and incriment the global Component<T> type count
  Component() {
    if(!type_created_) {
      type_id_ = g_component_type_count;
      g_component_type_count++;
      type_created_ = true;
    }
  }

  // Return the type_id associated with this component type
  // int type_id = Component<MyType>::type_id()
  static int type_id() {
    return type_id_;
  }

  virtual ~Component() {};

  static bool type_created_;
  static int type_id_;
};

template <typename T>
bool ecs::Component<T>::type_created_ = false ;
template <typename T>
int ecs::Component<T>::type_id_ = -1;

}
