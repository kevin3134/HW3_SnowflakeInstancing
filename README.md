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
##### 1，

### 实际做法：
##### 1，

### bug和未来的优化：
##### 1，透明度计算时，存在顺序问题，目前是按照初始位置z排序画instance，但镜头移动和物体随机移动（目前随机移动没有动z）后可能会出现遮挡问题
##### 2，随机移动的部分，还有优化空间
##### 3，存在一些magic number

### 使用库：
###### glm，glad，glfw

### 参考：
###### 1，learnopengl，主要关注instancing，blend相关的
https://learnopengl.com/
