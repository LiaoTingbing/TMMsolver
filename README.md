
# 传输矩阵法C++代码实现

## 原理
传输矩阵法是一种用于分析和设计多层光学、电磁学或声学系统的方法。它通过将系统分解为一系列基本层，并利用矩阵运算来描述每层对波的传播特性的影响，从而高效地计算整个系统的传输或反射特性。这种方法广泛应用于光学薄膜设计、光波导分析、声学多层结构分析等领域。



![](images/p1.png)

## 使用
使用Visual Studio 2022开发，C++矩阵计算库Armadillo。
### 安装
Visual Studio 2022安装Armadillo

	git clone https://github.com/microsoft/vcpkg.git
	cd vcpkg
	.\bootstrap-vcpkg.bat
	.\vcpkg install Armadillo
	.\vcpkg integrate install

### 文件目录说明

```
    E:.
│  .gitattributes
│  .gitignore
│  common.h
│  content.json
│  Device.cpp
│  Device.h
│  main.cpp
│  README.md
│  TMM.sln
│  TMM.vcxproj
│  TMM.vcxproj.filters
│  TMM.vcxproj.user
│  tree.txt
│  userFunc.cpp
│  userFunc.h
│  
├─images
│      p1.png
│      新建 Microsoft PowerPoint 演示文稿.png
│      新建 Microsoft PowerPoint 演示文稿.pptx
│      
├─src
├─TMM
│  └─x64
│      ├─Debug
│      │  │  Device.obj
│      │  │  main.obj
│      │  │  TMM.exe.recipe
│      │  │  TMM.ilk
│      │  │  TMM.log
│      │  │  TMM.vcxproj.FileListAbsolute.txt
│      │  │  userFunc.obj
│      │  │  vc143.idb
│      │  │  vc143.pdb
│      │  │  vcpkg.applocal.log
│      │  │  
│      │  └─TMM.tlog
│      │          CL.command.1.tlog
│      │          Cl.items.tlog
│      │          CL.read.1.tlog
│      │          CL.write.1.tlog
│      │          link.command.1.tlog
│      │          link.read.1.tlog
│      │          link.secondary.1.tlog
│      │          link.write.1.tlog
│      │          TMM.lastbuildstate
│      │          TMM.write.1u.tlog
│      │          
│      └─Release
│          │  Device.obj
│          │  main.obj
│          │  TMM.exe.recipe
│          │  TMM.iobj
│          │  TMM.ipdb
│          │  TMM.log
│          │  TMM.vcxproj.FileListAbsolute.txt
│          │  userFunc.obj
│          │  vc143.pdb
│          │  vcpkg.applocal.log
│          │  
│          └─TMM.tlog
│                  CL.command.1.tlog
│                  Cl.items.tlog
│                  CL.read.1.tlog
│                  CL.write.1.tlog
│                  link.command.1.tlog
│                  link.read.1.tlog
│                  link.secondary.1.tlog
│                  link.write.1.tlog
│                  TMM.lastbuildstate
│                  TMM.write.1u.tlog
│                  
└─x64
    ├─Debug
    │      libgcc_s_seh-1.dll
    │      libgfortran-5.dll
    │      liblapack.dll
    │      libquadmath-0.dll
    │      libwinpthread-1.dll
    │      openblas.dll
    │      TMM.exe
    │      TMM.pdb
    │      
    └─Release
            libgcc_s_seh-1.dll
            libgfortran-5.dll
            liblapack.dll
            libquadmath-0.dll
            libwinpthread-1.dll
            openblas.dll
            TMM.exe
            TMM.pdb
```


### 用法
器件结构的输入文件为content.json，数据结构如下
	
	{
    "device": [
        {
            "thickness": 1e-6,
            "indexReal": 1,
            "indexImag": 0.01
        },
        {
            "thickness": 1e-6,
            "indexReal": 1,
            "indexImag": 0.01
        },
        ...
        {
            "thickness": 1e-6,
            "indexReal": 3,
            "indexImag": 0.8
        }
    ],
    "source": {
        "theta": 75, 
        "lambda": 0.8e-6
    }
}

## 测试结果
