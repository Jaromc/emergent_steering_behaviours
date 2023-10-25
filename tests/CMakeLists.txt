add_executable(Vector2_tests Vector2_tests.cpp)

add_test(
  NAME Vector2_tests
  COMMAND $<TARGET_FILE:Vector2_tests>
  )