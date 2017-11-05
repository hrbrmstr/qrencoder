
<!-- README.md is generated from README.Rmd. Please edit that file -->
`qrencoder` : Make QR codes in R

There is another package on CRAN -- `qrcode` -- that is not C-backed.

Quick Response codes (QR codes) are a type of matrix bar code and can be used to authenticate transactions, provide access to multi-factor authentication services and enable general data transfer in an image. QR codes use four standardized encoding modes (numeric, alphanumeric, byte/binary, and kanji) to efficiently store data. Matrix barcode generation is performed efficiently in C via the included 'libqrencoder' library created by Kentaro Fukuchi.

The following functions are implemented:

-   `qrencode`: Return a QR encoded string as a matrix
-   `qrencode_df`: Return a QR encoded string as an x, y, z data.frame
-   `qrencode_png`: Return a QR encoded string as a base 64 encoded inline png
-   `qrencode_raster`: Return a QR encoded string as a raster object
-   `qrencode_svg`: Return a QR encoded string as an svg string

### Installation

``` r
devtools::install_github("hrbrmstr/qrencoder")
```

### Usage

``` r
library(qrencoder)
#> Loading required package: raster
#> Loading required package: sp

# current verison
packageVersion("qrencoder")
#> [1] '0.2.1'

url <- "http://rud.is/b"
head(qrencode(url))
#>      [,1] [,2] [,3] [,4] [,5] [,6] [,7] [,8] [,9] [,10] [,11] [,12] [,13] [,14] [,15] [,16] [,17] [,18] [,19] [,20]
#> [1,]    1    1    1    1    1    1    1    0    1     0     0     0     0     0     1     1     1     1     1     1
#> [2,]    1    0    0    0    0    0    1    0    1     1     1     1     0     0     1     0     0     0     0     0
#> [3,]    1    0    1    1    1    0    1    0    0     0     1     1     1     0     1     0     1     1     1     0
#> [4,]    1    0    1    1    1    0    1    0    1     0     1     1     0     0     1     0     1     1     1     0
#> [5,]    1    0    1    1    1    0    1    0    0     1     1     0     1     0     1     0     1     1     1     0
#> [6,]    1    0    0    0    0    0    1    0    0     0     1     0     0     0     1     0     0     0     0     0
#>      [,21]
#> [1,]     1
#> [2,]     1
#> [3,]     1
#> [4,]     1
#> [5,]     1
#> [6,]     1

head(qrencode_df(url))
#>   x  y z
#> 1 0 20 1
#> 2 1 20 1
#> 3 2 20 1
#> 4 3 20 1
#> 5 4 20 1
#> 6 5 20 1

qrencode_png(url)
#> [1] "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABUAAAAVCAAAAACMfPpKAAAACXBIWXMAAC4jAAAuIwF4pT92AAAAfElEQVQYlU2QWwrEMAwDR0vuf+XZj8qJSyjIyNYjAkAMQNFhkBCKzoNiin70kxKBN41ENuf7+9AZWQOGRx/2m4TeKy2YO0GyDpwszW5EUCs/ur78NZtGvSa8azdPDGttsonot8LtDFNnrs4yLSbuJk0ajnV3vevhCxUj4Q+R11n764g4WgAAAABJRU5ErkJggg=="

qrencode_raster(url)
#> class       : RasterLayer 
#> dimensions  : 21, 21, 441  (nrow, ncol, ncell)
#> resolution  : 0.04761905, 0.04761905  (x, y)
#> extent      : 0, 1, 0, 1  (xmin, xmax, ymin, ymax)
#> coord. ref. : NA 
#> data source : in memory
#> names       : layer 
#> values      : 0, 1  (min, max)

par(mar=c(0,0,0,0))
image(qrencode_raster("http://rud.is/b"), 
      asp=1, col=c("white", "black"), axes=FALSE, 
      xlab="", ylab="")
```

![](README-qr-1.png)

### SVG

``` r
cat(qrencode_svg(url))
#> <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
#> <!-- Created with qrencode 3.9.0 (http://fukuchi.org/works/qrencode/index.html.en) -->
#> <svg width="2.01cm" height="2.01cm" viewBox="0 0 19 19" preserveAspectRatio="none" version="1.1" xmlns="http://www.w3.org/2000/svg">
#>  <g id="QRcode">
#>      <rect x="0" y="0" width="19" height="19" fill="#ffffff" />
#>      <g id="Pattern">
#>          <rect x="-1" y="-1" width="7" height="1" fill="#000000" />
#>          <rect x="8" y="-1" width="1" height="1" fill="#000000" />
#>          <rect x="11" y="-1" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="-1" width="7" height="1" fill="#000000" />
#>          <rect x="-1" y="0" width="1" height="1" fill="#000000" />
#>          <rect x="5" y="0" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="0" width="2" height="1" fill="#000000" />
#>          <rect x="10" y="0" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="0" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="0" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="1" width="1" height="1" fill="#000000" />
#>          <rect x="1" y="1" width="3" height="1" fill="#000000" />
#>          <rect x="5" y="1" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="1" width="2" height="1" fill="#000000" />
#>          <rect x="10" y="1" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="1" width="1" height="1" fill="#000000" />
#>          <rect x="15" y="1" width="3" height="1" fill="#000000" />
#>          <rect x="19" y="1" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="2" width="1" height="1" fill="#000000" />
#>          <rect x="1" y="2" width="3" height="1" fill="#000000" />
#>          <rect x="5" y="2" width="1" height="1" fill="#000000" />
#>          <rect x="8" y="2" width="1" height="1" fill="#000000" />
#>          <rect x="10" y="2" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="2" width="1" height="1" fill="#000000" />
#>          <rect x="15" y="2" width="3" height="1" fill="#000000" />
#>          <rect x="19" y="2" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="3" width="1" height="1" fill="#000000" />
#>          <rect x="1" y="3" width="3" height="1" fill="#000000" />
#>          <rect x="5" y="3" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="3" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="3" width="1" height="1" fill="#000000" />
#>          <rect x="15" y="3" width="3" height="1" fill="#000000" />
#>          <rect x="19" y="3" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="4" width="1" height="1" fill="#000000" />
#>          <rect x="5" y="4" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="4" width="1" height="1" fill="#000000" />
#>          <rect x="10" y="4" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="4" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="4" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="5" width="7" height="1" fill="#000000" />
#>          <rect x="7" y="5" width="1" height="1" fill="#000000" />
#>          <rect x="9" y="5" width="1" height="1" fill="#000000" />
#>          <rect x="11" y="5" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="5" width="7" height="1" fill="#000000" />
#>          <rect x="7" y="6" width="3" height="1" fill="#000000" />
#>          <rect x="11" y="6" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="7" width="2" height="1" fill="#000000" />
#>          <rect x="2" y="7" width="1" height="1" fill="#000000" />
#>          <rect x="5" y="7" width="2" height="1" fill="#000000" />
#>          <rect x="8" y="7" width="2" height="1" fill="#000000" />
#>          <rect x="13" y="7" width="3" height="1" fill="#000000" />
#>          <rect x="17" y="7" width="2" height="1" fill="#000000" />
#>          <rect x="0" y="8" width="1" height="1" fill="#000000" />
#>          <rect x="3" y="8" width="1" height="1" fill="#000000" />
#>          <rect x="10" y="8" width="3" height="1" fill="#000000" />
#>          <rect x="15" y="8" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="8" width="1" height="1" fill="#000000" />
#>          <rect x="0" y="9" width="6" height="1" fill="#000000" />
#>          <rect x="7" y="9" width="1" height="1" fill="#000000" />
#>          <rect x="11" y="9" width="2" height="1" fill="#000000" />
#>          <rect x="14" y="9" width="1" height="1" fill="#000000" />
#>          <rect x="17" y="9" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="9" width="1" height="1" fill="#000000" />
#>          <rect x="0" y="10" width="3" height="1" fill="#000000" />
#>          <rect x="6" y="10" width="6" height="1" fill="#000000" />
#>          <rect x="13" y="10" width="1" height="1" fill="#000000" />
#>          <rect x="15" y="10" width="2" height="1" fill="#000000" />
#>          <rect x="18" y="10" width="2" height="1" fill="#000000" />
#>          <rect x="1" y="11" width="1" height="1" fill="#000000" />
#>          <rect x="3" y="11" width="1" height="1" fill="#000000" />
#>          <rect x="5" y="11" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="11" width="1" height="1" fill="#000000" />
#>          <rect x="11" y="11" width="2" height="1" fill="#000000" />
#>          <rect x="14" y="11" width="1" height="1" fill="#000000" />
#>          <rect x="16" y="11" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="12" width="1" height="1" fill="#000000" />
#>          <rect x="11" y="12" width="2" height="1" fill="#000000" />
#>          <rect x="14" y="12" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="12" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="13" width="7" height="1" fill="#000000" />
#>          <rect x="7" y="13" width="2" height="1" fill="#000000" />
#>          <rect x="11" y="13" width="2" height="1" fill="#000000" />
#>          <rect x="15" y="13" width="4" height="1" fill="#000000" />
#>          <rect x="-1" y="14" width="1" height="1" fill="#000000" />
#>          <rect x="5" y="14" width="1" height="1" fill="#000000" />
#>          <rect x="8" y="14" width="1" height="1" fill="#000000" />
#>          <rect x="15" y="14" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="14" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="15" width="1" height="1" fill="#000000" />
#>          <rect x="1" y="15" width="3" height="1" fill="#000000" />
#>          <rect x="5" y="15" width="1" height="1" fill="#000000" />
#>          <rect x="8" y="15" width="2" height="1" fill="#000000" />
#>          <rect x="12" y="15" width="1" height="1" fill="#000000" />
#>          <rect x="14" y="15" width="3" height="1" fill="#000000" />
#>          <rect x="-1" y="16" width="1" height="1" fill="#000000" />
#>          <rect x="1" y="16" width="3" height="1" fill="#000000" />
#>          <rect x="5" y="16" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="16" width="3" height="1" fill="#000000" />
#>          <rect x="11" y="16" width="1" height="1" fill="#000000" />
#>          <rect x="13" y="16" width="3" height="1" fill="#000000" />
#>          <rect x="18" y="16" width="2" height="1" fill="#000000" />
#>          <rect x="-1" y="17" width="1" height="1" fill="#000000" />
#>          <rect x="1" y="17" width="3" height="1" fill="#000000" />
#>          <rect x="5" y="17" width="1" height="1" fill="#000000" />
#>          <rect x="8" y="17" width="4" height="1" fill="#000000" />
#>          <rect x="13" y="17" width="1" height="1" fill="#000000" />
#>          <rect x="15" y="17" width="1" height="1" fill="#000000" />
#>          <rect x="17" y="17" width="1" height="1" fill="#000000" />
#>          <rect x="19" y="17" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="18" width="1" height="1" fill="#000000" />
#>          <rect x="5" y="18" width="1" height="1" fill="#000000" />
#>          <rect x="7" y="18" width="2" height="1" fill="#000000" />
#>          <rect x="10" y="18" width="2" height="1" fill="#000000" />
#>          <rect x="14" y="18" width="1" height="1" fill="#000000" />
#>          <rect x="16" y="18" width="1" height="1" fill="#000000" />
#>          <rect x="-1" y="19" width="7" height="1" fill="#000000" />
#>          <rect x="7" y="19" width="3" height="1" fill="#000000" />
#>          <rect x="13" y="19" width="1" height="1" fill="#000000" />
#>          <rect x="18" y="19" width="1" height="1" fill="#000000" />
#>      </g>
#>  </g>
#> </svg>
```

![](https://rud.is/dl/qr.svg)

### Test Results

``` r
library(qrencoder)
library(testthat)

date()
#> [1] "Sun Nov  5 08:04:50 2017"

test_dir("tests/")
#> testthat results ========================================================================================================
#> OK: 0 SKIPPED: 0 FAILED: 0
#> 
#> DONE ===================================================================================================================
```

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
