# CCSDS 123.0-B-2 Hardware Implementation

This repository contains source codes for a hardware implementation of hyperspectral image compression compatible with the CCSDS 123.0-B-2 standard.
 
This work is part of research projects that I have participated as a student of the Computer Engineering degree and conclusion work of my graduation. The objective was to implement a hardware accelerator for the compression of hyperspectral images for use in space systems. For this, a compression standard known in space applications was adopted, the CCSDS 123, developed by the Consultative Committee for Space Data Systems. Currently this standard is in version B-2 and presents compression with and without data losses for multispectral and hyperspectral images. This compressor model is based on a sample prediction model, followed by an encoder as can be seen in the image below.

![alt text](https://github.com/[wesleygrignani]/[CCSDS123.0-B-2_Implementation]/images/[main]/ccsds123_block.png?raw=true)

Thus, this work considered this mentioned compression standard. Initially a high level C language version was implemented from the specification, in order to validate the application and to serve as a basis for the hardware implementation later on. The goal of this work was to make an implementation with the lowest hardware resource utilization possible, but still be able to accelerate the compression application. Therefore, some design choices were made in the implementation to decrease the level of complexity and hardware resource usage. 

The standard presents a series of steps that must be implemented. The entire prediction process was performed over the reduced mode, thus eliminating some additional calculations that would give more precision to the prediction model but would use more resources. In addition, the local sum step was performed in the column-oriented mode, due to the fact that it only requires the neighboring pixel above, using fewer resources in comparison with the other models. The compression mode adopted was BIP (Band interleaved by pixel) in order to facilitate the hardware implementation logic along with the choices commented above. The encoding block model implemented was the sample-adaptive one. This choice was made because, according to the standard, it presented better results when the compression model chosen was the lossless one, the same as in this project. 
