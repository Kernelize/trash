# Build commands

1. build the llvm-project and clang
```bash
git clone llvm-url
cmake -S llvm -B build -G Ninja -DCMAKE_INSTALL_PREFIX=/opt/llvm -DCMAKE_BUILD_TYPE=MinSizeRel -DLLVM_PARALLEL_COMPILE_JOBS=10 -DLLVM_PARALLEL_LINK_JOBS=10 -DLLVM_ENABLE_PROJECTS="clang;lld;clang-tools-extra;polly" -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++ -DCMAKE_C_COMPILER=/opt/homebrew/opt/llvm/bin/clang -DDEFAULT_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk -DLLVM_ENABLE_RUNTIMES="compiler-rt;libcxx;libcxxabi;libunwind" -DCMAKE_OSX_ARCHITECTURES='arm64' -DLLVM_TARGETS_TO_BUILD='AArch64' -DLIBCXX_INSTALL_MODULES=ON
cmake --build build
sudo ninja -C build install
```

2. build the project
```bash
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=/opt/llvm/bin/clang++ -DCMAKE_C_COMPILER=/opt/llvm/bin/clang
```
