#pragma once

class CustomIterate : public Supla::Element {
 public:
  CustomIterate() {}

  void iterateAlways() {
    if (status1 != status2){
      relay_->toggle();
      status2 = status1;
    }
  }
};  // CustomIterate

CustomIterate cIterate;