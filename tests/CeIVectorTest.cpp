#include <stdlib.h>

#include <gtest/gtest.h>

#include <ceivector.h>

// ---------------------------------------------------------------------------------

int* make_integer(int n)
{
    int* integer = (int*) malloc(sizeof(int));
    *integer = n;

    return integer;
}

TEST(CeIVectorTest, should_be_able_to_handle_elements)
{
    // Testing get/set element when out of bound, so as front/back when empty vec,
    // currently returns a sentinel element. Should be a NULL instead? Not sure,
    // since it's a vector of pointers, NULL *could* be an actual value, but would
    // more likely a bug in user code

    ce_ivector_t ceVec = ce_ivector_new_with_default_deleter();

    ASSERT_TRUE(ce_ivector_empty(ceVec));
    ASSERT_EQ(ce_ivector_capacity(ceVec), 32);
    ASSERT_EQ(ce_ivector_size(ceVec), 0);

    ASSERT_EQ(ce_ivector_get_element(ceVec, 0), ce_ivector_sentinel_value(ceVec));
    ASSERT_EQ(ce_ivector_front(ceVec), ce_ivector_sentinel_value(ceVec));
    ASSERT_EQ(ce_ivector_back(ceVec), ce_ivector_sentinel_value(ceVec));

    for (int i = 42; i >= 11; i--)
    {
        ce_ivector_push_back(ceVec, make_integer(i));
    }

    ASSERT_FALSE(ce_ivector_empty(ceVec));
    ASSERT_EQ(ce_ivector_capacity(ceVec), 32);
    ASSERT_EQ(ce_ivector_size(ceVec), 32);

    ce_ivector_push_back(ceVec, make_integer(10));

    ASSERT_EQ(ce_ivector_capacity(ceVec), 64);
    ASSERT_EQ(ce_ivector_size(ceVec), 33);

    ce_ivector_reserve(ceVec, 63);
    ASSERT_EQ(ce_ivector_capacity(ceVec), 64);

    ce_ivector_reserve(ceVec, 65);
    ASSERT_EQ(ce_ivector_capacity(ceVec), 65);

    int expectedKey = 42;
    for (int i = 0; i < ce_ivector_size(ceVec); i++)
    {
        const int currentKey = *(int*)ce_ivector_get_element(ceVec, i);
        ASSERT_EQ(currentKey, expectedKey--);
    }

    ASSERT_EQ(*(int*)ce_ivector_front(ceVec), 42);
    ASSERT_EQ(*(int*)ce_ivector_back(ceVec), 10);

    const int lastPos = ce_ivector_size(ceVec) - 1;
    int* oldElement = (int*)ce_ivector_get_element(ceVec, lastPos);
    int* newElement = make_integer(100);
    ce_ivector_set_element(ceVec, lastPos + 1, newElement);
    ASSERT_EQ(ce_ivector_get_element(ceVec, lastPos), oldElement);
    ce_ivector_set_element(ceVec, lastPos, newElement);
    ASSERT_EQ(ce_ivector_get_element(ceVec, lastPos), newElement);
    ASSERT_EQ(ce_ivector_back(ceVec), newElement);
    ASSERT_EQ(ce_ivector_get_element(ceVec, lastPos + 1), ce_ivector_sentinel_value(ceVec));
    ASSERT_EQ(*(int*)ce_ivector_back(ceVec), 100);

    ce_ivector_clear(ceVec);
    ASSERT_TRUE(ce_ivector_empty(ceVec));
    ASSERT_EQ(ce_ivector_capacity(ceVec), 65);
    ASSERT_EQ(ce_ivector_size(ceVec), 0);

    ce_ivector_push_back(ceVec, make_integer(123));
    ce_ivector_push_back(ceVec, make_integer(321));

    ASSERT_FALSE(ce_ivector_empty(ceVec));
    ASSERT_EQ(ce_ivector_capacity(ceVec), 65);
    ASSERT_EQ(ce_ivector_size(ceVec), 2);

    ce_ivector_pop_back(ceVec);
    ce_ivector_pop_back(ceVec);

    ASSERT_TRUE(ce_ivector_empty(ceVec));
    ASSERT_EQ(ce_ivector_capacity(ceVec), 65);
    ASSERT_EQ(ce_ivector_size(ceVec), 0);

    ce_ivector_del(ceVec);
}

// ---------------------------------------------------------------------------------

int deletedElements[4];
int countDeletedElements = 0;

void custom_destructor(void* element)
{
    deletedElements[countDeletedElements++] = *(int*)element;
    free(element);
}

TEST(CeIVectorTest, should_be_able_to_use_a_custom_deleter)
{
    ce_ivector_t ceVec = ce_ivector_new_with_custom_deleter(custom_destructor);

    ASSERT_EQ(countDeletedElements, 0);
    ce_ivector_push_back(ceVec, make_integer(42));
    ce_ivector_pop_back(ceVec);
    ASSERT_EQ(countDeletedElements, 1);

    ce_ivector_push_back(ceVec, make_integer(24));
    ce_ivector_push_back(ceVec, make_integer(321));
    ce_ivector_set_element(ceVec, 0, make_integer(123));
    ce_ivector_del(ceVec);

    ASSERT_EQ(countDeletedElements, 4);
    ASSERT_EQ(deletedElements[0], 42);
    ASSERT_EQ(deletedElements[1], 24);
    ASSERT_EQ(deletedElements[2], 123);
    ASSERT_EQ(deletedElements[3], 321);
}

// ---------------------------------------------------------------------------------
