#include <Rcpp.h>
#include <string.h>
#include "qrencode.h"

using namespace Rcpp;

//' @title Encodes a string as a QR code
//' @param to_encode character string to encode
//' @export
//[[Rcpp::export]]
NumericMatrix qrencode_raw(std::string to_encode) {

  QRcode *code ;

  code = QRcode_encodeString8bit(to_encode.c_str(), 0, QR_ECLEVEL_H);

  NumericMatrix qr(code->width, code->width);

  for (int i=0; i<code->width; i++) {
    for (int j=0; j<code->width; j++) {
      qr(i, j) = (code->data[(code->width*i)+j] & 1);
    }
  }

  return(qr);

}
