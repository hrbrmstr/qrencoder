<!-- README.md is generated from README.Rmd. Please edit that file -->
qrencoder uses `libqrencode` to make QR codes in R

The following functions are implemented:

-   `qrencode`: Return a QR encoded string as a matrix
-   `qrencode_df`: Return a QR encoded string as an x, y, z data.frame
-   `qrencode_png`: Return a QR encoded string as a base 64 encoded inline png
-   `qrencode_raster`: Return a QR encoded string as a raster object

NOTE: You'll need `Rcpp`, `base64enc`, `raster` & `png` installed (and, `libqrencode` of course).

Not tested under Windows.

### News

-   Version released

### Installation

``` r
devtools::install_github("hrbrmstr/qrencoder")
```

### Usage

``` r
library(qrencoder)
library(raster)
#> Loading required package: sp

# current verison
packageVersion("qrencoder")
#> [1] '0.0.0.9000'

url <- "http://rud.is/b"
head(qrencode(url))
#>      [,1] [,2] [,3] [,4] [,5] [,6] [,7] [,8] [,9] [,10] [,11] [,12] [,13] [,14] [,15] [,16] [,17] [,18] [,19] [,20]
#> [1,]    1    1    1    1    1    1    1    0    0     1     0     1     1     0     0     0     1     0     0     1
#> [2,]    1    0    0    0    0    0    1    0    0     0     0     1     1     1     1     0     1     1     0     1
#> [3,]    1    0    1    1    1    0    1    0    1     0     0     0     1     0     1     0     0     0     1     1
#> [4,]    1    0    1    1    1    0    1    0    1     0     0     1     0     0     0     1     1     1     0     0
#> [5,]    1    0    1    1    1    0    1    0    0     0     1     1     0     1     1     0     1     0     1     1
#> [6,]    1    0    0    0    0    0    1    0    0     1     0     1     0     1     1     1     0     0     0     0
#>      [,21] [,22] [,23] [,24] [,25] [,26] [,27] [,28] [,29]
#> [1,]     1     0     1     1     1     1     1     1     1
#> [2,]     0     0     1     0     0     0     0     0     1
#> [3,]     0     0     1     0     1     1     1     0     1
#> [4,]     1     0     1     0     1     1     1     0     1
#> [5,]     1     0     1     0     1     1     1     0     1
#> [6,]     0     0     1     0     0     0     0     0     1

head(qrencode_df(url))
#>   x  y z
#> 1 0 28 1
#> 2 1 28 1
#> 3 2 28 1
#> 4 3 28 1
#> 5 4 28 1
#> 6 5 28 1

qrencode_png(url)
#> [1] "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB0AAAAdCAAAAABz+DjTAAAACXBIWXMAAC4jAAAuIwF4pT92AAAA40lEQVQokU2TWxKEQAgDO1tz/yv3fvBSq9SCgYQEIwAEIwGDpKOPAAgBJBhCR3+gTj6QrlPhcZchFgjTmQUGiYPZ2UylXd+ngYeb/NwdzbVx2F/wByhFu5AHqSeZN1jUqgB5mA7MOPghNgN0B3Hl8VctLH1JV9rTDYq64FwFV1ZI8ePZfZeM6xXkjcQQKJVSofSwJUc/2j5Xq3DKtl5l2atIyEzeHGmmGZbj1Dp+dnhuOY3yvjsZbxWIB7ZKc3bqm221GLCH02osC9fKGMhnJyvS/0L/DbeTw1OaXIs/uXwolOZ/QFfD+4NkWyYAAAAASUVORK5CYII="

qrencode_raster(url)
#> class       : RasterLayer 
#> dimensions  : 29, 29, 841  (nrow, ncol, ncell)
#> resolution  : 0.03448276, 0.03448276  (x, y)
#> extent      : 0, 1, 0, 1  (xmin, xmax, ymin, ymax)
#> coord. ref. : NA 
#> data source : in memory
#> names       : layer 
#> values      : 0, 1  (min, max)

image(qrencode_raster("http://rud.is/b"), 
      asp=1, col=c("black", "white"), axes=FALSE, 
      xlab="", ylab="")
```

![](README-qr-1.png)

### Test Results

``` r
library(qrencoder)
library(testthat)

date()
#> [1] "Sun Aug  2 11:30:30 2015"

test_dir("tests/")
#> testthat results ========================================================================================================
#> OK: 0 SKIPPED: 0 FAILED: 0
#> 
#> DONE
```

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
