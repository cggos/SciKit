# MatlabProjects
Matlab Projects :bar_chart:

## Matlab生成DLL，与C++混合编程
### 编写Matlab函数文件，例如 CircleDetect.m
```
function [accum, circen, cirrad] = CircleDetect(imggray)
......
```
### 选择编译器
`mex -setup`，选择VS2010编译器
### 选择builder
`mbuild -setup`，选择VS2010 builder
### 生成.h、.lib、.DLL等文件
`mcc -W cpplib:CircleDetectLib -T link:lib CircleDetect.m -d ./output`，生成.h、.lib、.DLL等文件，.h文件函数接口如下所示：
```   
  extern LIB_CircleDetectLib_C_API
  bool MW_CALL_CONV CircleDetectLibInitializeWithHandlers(
         mclOutputHandlerFcn error_handler,
         mclOutputHandlerFcn print_handler);

  extern LIB_CircleDetectLib_C_API
  bool MW_CALL_CONV CircleDetectLibInitialize(void);

  extern LIB_CircleDetectLib_C_API
  void MW_CALL_CONV CircleDetectLibTerminate(void);



  extern LIB_CircleDetectLib_C_API
  void MW_CALL_CONV CircleDetectLibPrintStackTrace(void);

  extern LIB_CircleDetectLib_C_API
  bool MW_CALL_CONV mlxCircleDetect(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

  extern LIB_CircleDetectLib_C_API
  long MW_CALL_CONV CircleDetectLibGetMcrID();
```
### C++调用Matlab接口
核心代码如下所示：
```
int DetectCircles(std::string pathImg,vector<CPoint2Df> &vecCenters,vector<float> &vecRads)
{
	if (!CircleDetectLibInitialize())
	{
		return -1;
	}

	mwArray accum_mat,circen_mat,cirrad_mat;
	const char *chImg = pathImg.c_str();
	mwArray imageNameArray(chImg);

	CircleDetect(3,accum_mat,circen_mat,cirrad_mat,imageNameArray);

	const int nCount = circen_mat.GetDimensions();
	double *pCenterDataArr = new double[2*nCount];
	double *pRadsDataArr = new double[nCount];

	circen_mat.GetData(pCenterDataArr,2*nCount);
	cirrad_mat.GetData(pRadsDataArr,nCount);

	CPoint2Df tempPt;
	for (int i=0;i<nCount;i++)
	{
		tempPt.x = (float)pCenterDataArr[i];
		tempPt.y = (float)pCenterDataArr[i+nCount];
		vecCenters.push_back(tempPt);
		vecRads.push_back(float(pRadsDataArr[i]));
	}

	delete[] pCenterDataArr;
	delete[] pRadsDataArr;

	CircleDetectLibTerminate();

	return 0;
}

```
### 部署Matlab DLL
如果需要在其他未装Matlab的机器上运行，则还需要将“D:\Program Files\MATLAB\R2010b\toolbox\compiler\deploy\win64”中的**MCRInstaller.exe**复制出来，在未安装Matlab的电脑上运行此程序，才可使得刚刚生成的可执行文件顺利运行。

## Issues
* Q: MATLAB卸载时出现exception calling main  
A: 桌面点右键->个性化->更改计算机上的视觉效果和声音，选那个节目最朴素的经典桌面->确定，然后就能运行matlab的程序了，当然也可以运行其卸载程序
* Q: Win7下启动Matlab7.0时，出现一系列Java错误  
A: 在安装目录下，右击Matlab应用程序->属性->兼容性->勾选"以兼容模式运行这个程序"->选择Windows Vista SP1->勾选"以管理员身份运行此程序"->确定即可
