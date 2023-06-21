#include <gtest/gtest.h>
#include <thread>
#include "barbershop.hpp"

class BarbershopTest : public ::testing::Test {
protected:
    void SetUp() override {
        shop_open = true;
        max_waiting_clients = 5;
        waiting_queue = queue<int>();
    }

    void TearDown() override {
        shop_open = false;
    }
};

TEST_F(BarbershopTest, TestBarberShavesOneClient) {
    thread barber_thread(barber);
    thread client_thread(client, 0);
    this_thread::sleep_for(chrono::seconds(2));
    client_thread.join();
    barber_thread.join();
    ASSERT_EQ(waiting_queue.size(), 0);
}

TEST_F(BarbershopTest, TestBarberShavesMultipleClients) {
    thread barber_thread(barber);
    thread client_threads[5];
    for(int i=0; i<5; i++) {
        client_threads[i] = thread(client, i);
        this_thread::sleep_for(chrono::seconds(1));
    }
    this_thread::sleep_for(chrono::seconds(10));
    for(int i=0; i<5; i++) {
        client_threads[i].join();
    }
    barber_thread.join();
    ASSERT_EQ(waiting_queue.size(), 0);
}

TEST_F(BarbershopTest, TestBarberSleepsWhenNoClients) {
    thread barber_thread(barber);
    this_thread::sleep_for(chrono::seconds(5));
    ASSERT_TRUE(barber_sleeping);
    thread client_thread(client, 0);
    this_thread::sleep_for(chrono::seconds(2));
    ASSERT_FALSE(barber_sleeping);
    client_thread.join();
    barber_thread.join();
    ASSERT_EQ(waiting_queue.size(), 0);
}

TEST_F(BarbershopTest, TestClientLeavesWhenShopIsFull) {
    max_waiting_clients = 2;
    thread barber_thread(barber);
    thread client_threads[3];
    for(int i=0; i<3; i++) {
        client_threads[i] = thread(client, i);
        this_thread::sleep_for(chrono::seconds(1));
    }
    this_thread::sleep_for(chrono::seconds(5));
    for(int i=0; i<3; i++) {
        if (i < 2) {
            ASSERT_EQ(waiting_queue.front(), i);
            waiting_queue.pop();
        } else {
            ASSERT_EQ(waiting_queue.size(), 0);
        }
        client_threads[i].join();
    }
    barber_thread.join();
    ASSERT_EQ(waiting_queue.size(), 0);
}
