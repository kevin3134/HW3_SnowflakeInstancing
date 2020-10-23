## Billboard Instancing 广告牌实例化
#### （原为snowflake，雪花模拟）

![](https://img.shields.io/badge/platform-windows-lightgrey.svg)
![](https://img.shields.io/badge/language-C-orange.svg)
![](https://img.shields.io/badge/OpenGL-3.3-green.svg)

### 目标结果：
###### 用openGL模拟效果类似 https://threejs.org/examples/?q=partic#webgl_points_sprites 
###### 大致包含广告牌，透明度，实例化

### 结果参考：
##### 单个广告牌
![image](https://github.com/kevin3134/HW3_SnowflakeInstancing/blob/master/resource/billboard.png)
##### 广告牌实例化
![image](https://github.com/kevin3134/HW3_SnowflakeInstancing/blob/master/resource/billboardInstance.png)
##### 广告牌实例化加贴图
![image](https://github.com/kevin3134/HW3_SnowflakeInstancing/blob/master/resource/billboardInstanceTexture.png)
##### 动态气泡
![image](https://github.com/kevin3134/HW3_SnowflakeInstancing/blob/master/resource/bubbleInstaning.png)

### 思路：
##### 1，初始化一个可以有移动旋转相机，并贴上skybox的场景
##### 2，画出单个始终垂直相机方向的平面（面片）
##### 3，实例化面片，并随机位置
##### 4，面片加上透明贴图，并按从后向前排序
##### 5，面片动起来

### 实际做法：
##### 1，初始配置camera类，根据欧拉角旋转；配上立方体贴图
##### 2.1，~~先画出面片四个顶点，根据camera方向和面片平面向量计算角度（错误操作）~~
##### 2.2，先画出面片四个顶点，然后将面片旋转到面对照相机方向，用旋转矩阵或将view矩阵的前3*3改为单位矩阵（这种方法在camera位移后容易出错，不推荐） 
##### 2.3，在shader上根据 面向camera的平面的向量u，v，算出四个顶点，画出面片
##### 3，实例化使用drawElementInstance,并设置随机分布矩阵translation
##### 4，贴上RGBA的贴图；并enable blend；将分布矩阵按照照相机视角顺序从后向前排序
##### 5，创建速度矩阵，并在每一帧给随机加速度，让所有面片随机运动（可以在一定范围外给固定大小向原点加速度，保证面片不要全部乱飞出界）

### bug和未来的优化：
##### 1，透明度计算时，存在顺序问题，目前是按照初始位置z排序画instance，但镜头移动和物体随机移动（目前随机移动没有动z）后可能会出现遮挡问题
##### 2，随机移动的部分，还有优化空间
##### 3，存在一些magic number

### 使用库：
###### glm，glad，glfw

### 参考：
###### 1，learnopengl，主要关注instancing，blend相关的
https://learnopengl.com/
