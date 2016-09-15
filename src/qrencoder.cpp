#include <Rcpp.h>
#include "qrencode.h"

using namespace Rcpp;

//' @title Encodes a string as a QR code
//' @description Encodes a string as a QR coder
//' @param to_encode character string to encode
//' @param version version of the symbol. If \code{0}, the library chooses the
//'        minimum version for the given input data.
//' @param level error correction level (\code{0} - \code{3}, lowest to highest)
//' @param hint tell the library how Japanese Kanji characters should be
//'        encoded. If "\code{3}", the library assumes that the
//'        given string contains Shift-JIS characters and encodes them in
//'        Kanji-mode. If "\code{2}" is given, all of non-alphanumerical
//'        characters will be encoded as is. If you want to embed UTF-8
//'        string, choose this. Other mode will cause EINVAL error.\cr\cr
//'        "\code{0}" is "numeric mode", "\code{1}" is "alphanumeric mode",
//'        "\code{5}" is "ECI mode".
//' @param caseinsensitive case-sensitive(\code{1}) or not(\code{0}).
//' @seealso \url{http://www.qrcode.com/en/about/version.html}
//' @export
// [[Rcpp::export]]
NumericMatrix qrencode_raw(std::string to_encode,
                           int version=0,
                           int level=0,
                           int hint=2,
                           int caseinsensitive=1) {

  QRcode *qrcode ;
  unsigned char *row;
  int x, y;

  qrcode = QRcode_encodeString(to_encode.c_str(),
                               version,
                               (QRecLevel)level,
                               (QRencodeMode)hint, caseinsensitive);

  NumericMatrix qr(qrcode->width, qrcode->width);

  for(y=0; y <qrcode->width; y++) {
    row = qrcode->data+(y*qrcode->width);
    for(x = 0; x < qrcode->width; x++) {
      qr(x, y) = row[x]&0x1;
    }
  }

  return(qr);

}
