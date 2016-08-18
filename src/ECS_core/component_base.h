#pragma once

class ComponentBase {
public:
  virtual ~ComponentBase() = default; // Will cause derived class destructor to be called
};
