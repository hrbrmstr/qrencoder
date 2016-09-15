#' Quick Response Code (QR Code) / Matrix Barcode Creator
#'
#' Quick Response codes (QR codes) are a type of matrix bar code and can be
#' used to authenticate transactions, provide access to multi-factor authenticationan
#' services and enable general data transfer in an image. QR codes use four standardized
#' encoding modes (numeric, alphanumeric, byte/binary, and kanji) to efficiently store
#' data. Matrix barcode generation is performed efficiently in C via the inlcuded
#' 'libqrencoder' library created by Kentaro Fukuchi.
#'
#' @name qrencoder
#' @docType package
#' @author Bob Rudis (bob@@rud.is)
#' @useDynLib qrencoder
#' @importFrom Rcpp sourceCpp
#' @importFrom png writePNG
#' @importFrom raster raster
NULL
