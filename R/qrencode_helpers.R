#' Return a QR encoded string as a raster object
#'
#' @param to_encode the data to encode
#' @export
#' @import raster
#' @examples
#' library(raster)
#' old_mar <- par()$mar
#' par(mar=c(0,0,0,0))
#' image(qrencode_raster("http://rud.is/b"), asp=1, col=c("white", "black"),
#'                                           axes=FALSE, xlab="", ylab="")
#' par(mar=old_mar)
qrencode_raster <- function(to_encode) {
  raster(qrencode_raw(to_encode))
}

#' Return a QR encoded string as an x, y, z data.frame
#'
#' Useful for ggplot::geom_raster
#'
#' @param to_encode the data to encode
#' @export
#' @examples
#' head(qrencode_df("http://rud.is/b"))
qrencode_df <- function(to_encode) {
  to_xyz(qrencode_raw(to_encode))
}

#' Return a QR encoded string as a matrix
#'
#' Useful if you want to do your own post-processing
#'
#' @param to_encode the data to encode
#' @export
#' @examples
#' qrencode("http://rud.is/b")
qrencode <- function(to_encode) {
  qrencode_raw(to_encode)
}

#' Return a QR encoded string as a base 64 encoded inline png
#'
#' @param to_encode the data to encode
#' @note \code{data:image/png;base64,} is prepended to the encoded png
#' @import base64enc
#' @import png
#' @export
#' @examples
#' cat(qrencode_png("http://rud.is/b"))
qrencode_png <- function(to_encode) {

  tmp <- qrencode_raw(to_encode)
  fil <- tempfile(pattern="qr", fileext=".png")
  writePNG(tmp, fil, dpi=300)
  out <- paste0("data:image/png;base64,", base64encode(fil))
  unlink(fil)
  out

}
