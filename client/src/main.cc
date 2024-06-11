#include <iostream>
#include <thread>

#include "client.h"

int main(int argc, char** argv) {
  RobotControlAsyncClientImpl client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

  std::cout << "Moving to (0, 0)" << std::endl;
  client.Move(0, 0);

  std::cout << "Stopping robot" << std::endl;
  client.Stop();

  std::cout << "Moving to (10, 20)" << std::endl;
  client.AsyncMove(10, 20);

  std::thread th = std::thread(&RobotControlAsyncClientImpl::Run, &client);

  client.AsyncMove2(10, 20);

  client.Shutdown();
  th.join();

  return 0;
}
