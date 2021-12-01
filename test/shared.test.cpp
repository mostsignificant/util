#include <string>

#include "gtest/gtest.h"
#include "test.hpp"
#include "util/shared.hpp"

TEST(UtilShared, CtorDefault) {
    //! [shared_ctor_default]
    util::shared<std::string> name;
    //! [shared_ctor_default]
}

TEST(UtilShared, Dtor) {
    class dtor_flag {  // NOLINT
        bool* flag = nullptr;

    public:
        dtor_flag(bool* flag) : flag(flag) {}
        ~dtor_flag() { *flag = true; }
    };

    bool deleted = false;
    { util::shared<dtor_flag> sh(new dtor_flag(&deleted)); }

    assert(deleted);
}

TEST(UtilShared, UseCount) {
    //! [shared_use_count]
    util::shared<std::string> name(new std::string("Chris"));
    assert(name.use_count() == 1);
    //! [shared_use_count]

    util::shared<std::string> name2(name);
    assert(name.use_count() == 2);
}