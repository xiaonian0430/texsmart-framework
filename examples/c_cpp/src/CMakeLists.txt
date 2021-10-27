cmake_minimum_required(VERSION 2.8)

add_executable(nlu_c_example1 nlu_c_example1.c)
target_link_libraries(nlu_c_example1 tencent_ai_texsmart)

add_executable(nlu_cpp_example1 nlu_cpp_example1.cc)
target_link_libraries(nlu_cpp_example1 tencent_ai_texsmart)

add_executable(nlu_cpp_example2 nlu_cpp_example2.cc)
target_link_libraries(nlu_cpp_example2 tencent_ai_texsmart)

#add_executable(nlu_cpp_example3 nlu_cpp_example3.cc)
#target_link_libraries(nlu_cpp_example3 tencent_ai_texsmart pthread)

set(executables_for_install
	nlu_c_example1
	nlu_cpp_example1
	nlu_cpp_example2
	#nlu_cpp_example3
	)
install(TARGETS ${executables_for_install} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT texsmart_examples)
