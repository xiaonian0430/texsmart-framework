
========== Build with cmake ==========

Build the debug version:
	Step-1: Create a sub-folder named "debug" in the "build.cmake" folder, and go to the folder:
		cd build.cmake; mkdir debug; cd debug
	Step-2: Setup a build:
		cmake ../../
		(or: cmake -DCMAKE_BUILD_TYPE=Debug ../../)
	Step-3: Build executables from source codes, and copy them to the binary folder:
		make install

	Upon a successful build, executables are generated and installed to
		${this_dir}/bin/debug/
	where ${this_dir} is the directory where this readme.md file resides.

Build the release version:

	Step-1: Create a sub-folder named "release" in the "build.cmake" folder, and go to the folder:
		cd build.cmake; mkdir release; cd release
	Step-2: Setup a build:
		cmake -DCMAKE_BUILD_TYPE=Release ../../
	Step-3: Build executables from source codes, and copy them to the binary folder:
		make install

	Upon a successful build, executables are generated and installed to
		${this_dir}/bin/release/

========== Build from Visual Studio ==========

Step-1: Open build.vs/examples.sln
Step-2: Build (Choose platform=x64, configuration=debug or release)
Please do NOT choose platform=x86, because the 32-bit version of the texsmart dll is not distributed so far.

Upon a successful build, executables are generated and installed to
	${this_dir}/bin/x64_${configuration}/
where ${configuration} is debug or release.

========== Frequently Asked Questions (FAQs) ==========
