CUDA Denoiser For CUDA Path Tracer
==================================

**University of Pennsylvania, CIS 565: GPU Programming and Architecture, Project 4**

* Xitong Zheng
  * [LinkedIn](https://www.linkedin.com/in/xitong-zheng-5b6543205/), [Instagram](https://www.instagram.com/simonz_zheng/), etc.
* Tested on: Windows 11, i7-12700k 32GB, GTX 4090 24GB

## Brief Intro
This project focuses on implementing CUDA denoiser from the paper [Edge-Avoiding À-Trous Wavelet Transform for fast Global
Illumination Filtering](https://jo.dreggn.org/home/2010_atrous.pdf)

### Details
| raw | denoised |
|-----| -----    |
|![](./img/intro_raw.png) | ![](./img/intro_denoised.png) |

### À-Trous Wavelet Filter
It approximates gaussian filter by iteratively applying sparse blurs of increasing size (stride size *= 2). It uses a small filter which spaces out the samples going through it, achieving far less read per pixels compared to gaussian filter when blur size increases. As for the À-Trous Wavelet Filter, increasing blur size means more iterations instead of larger filter size.
![](./img/filter_intro.png) 
The above picture shows that using a 5x5 filter to achieve 16x16 blur.

### G-buffer 
Edge-avoiding filtering is achieved by introducing a datadependent weighting function, which is related to weights calculated from the G-buffer that contains the normal and position data per-pixel.

Simple visualizations for the normal and position info of the G-buffer.

| Normal | Position |
|---|---|
|![](img/my_normal_G.png)|![](img/my_pos_G.png)|


### Performance Analysis
#### how much time denoising adds to your renders?
when the denoiser is activated, it runs each time after the call of pathtracer().

| pathtracing (with no denoiser) | pathtracing (with denoiser) |
|---|---|
| 79.23(milliseconds ) | 116.41(milliseconds) |

#### how denoising influences the number of iterations needed to get an "acceptably smooth" result?

| Denoised Output with 10 spp | Output with 500 spp | reference output at 5000 spp |
|---|---|---|
|![](img/intro_denoised.png)|![](img/500spp.png)|![](/img/ground_truth.png)|

Denoising can achieve the same smoothness in image with far less render iterations. When looking at the denoisied image at 10 iterations, most of the noise can be removed except that there are some issues around the edge and shadow of the scene. But when we focus on the walls and the floor, the image quality is quite good. You can see 500 iterations of standard the pathtracer can achieve similar result. So the denoiser can save around  50x iterations to achieve similar result.

#### how denoising at different resolutions impacts runtime?
![](./img/denoiser_runtime_resolution_(filter_size=80%20_%2080).png)

#### how varying filter sizes affect performance?
![](./img/Denoiser_runtime_VS_Filter_size_(resolution=1600%20_1600_10spp).png)

#### how visual results vary with filter size -- does the visual quality scale uniformly with filter size?

| 10 * 10 filter | 20 * 20 filter | 40 * 40 filter |  80 * 80 filter |
|---|---|---|---|
|![](img/10_10.png) | ![](img/20_20.png) | ![](img/40_40.png) | ![](img/80_80.png) |

#### how effective/ineffective is this method with different material types?
10spp
| Matarial Type | Original  | Denoised |
|---|---|---|
| Diffuse | ![](img/diffuse_original.png) | ![](img/diffuse.png) |
| Specular | ![](img/specular_original.png) | ![](img/specular.png) |

#### how do results compare across different scenes - for example, between cornell.txt and cornell_ceiling_light.txt. Does one scene produce better denoised results? Why or why not?

| scene | Original | Denoised |
|---|---|---|
| cornell | ![](img/cornell_original.png) | ![](img/cornell_denoised.png) |
| cornell_ceiling_light | ![](img/original_cornell_light.png) | ![](img/denoised_cornell_light.png) |
| cornell_light_emittance = 1 | ![](img/original_cornell_e1.png) | ![](img/denoised_cornell_e1.png) |