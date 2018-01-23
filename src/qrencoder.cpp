#include <Rcpp.h>
#include "qrencode.h"
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <streambuf>

using namespace Rcpp;

#define INCHES_PER_METER (100.0/2.54)

static int rle = 1;
static unsigned int fg_color[4] = {0, 0, 0, 255};
static unsigned int bg_color[4] = {255, 255, 255, 255};

//' @md
//' @title Encodes a string as a QR code
//' @description Encodes a string as a QR coder
//' @param to_encode character string to encode
//' @param version version of the symbol. If `0`, the library chooses the
//'        minimum version for the given input data.
//' @param level error correction level (`0` - `3`, lowest to highest)
//' @param hint tell the library how Japanese Kanji characters should be
//'        encoded:
//' - If "`3`", the library assumes that the given string contains Shift-JIS characters
//'   and encodes them in Kanji-mode.
//' - If "`2`" is given, all of non-alphanumerical characters will be encoded as is.
//'   If you want to embed UTF-8 string, choose this. Trying to encode UTF-8 with modes will cause an error.
//' - "`0`" is "numeric mode",
//' - "`1`" is "alphanumeric mode"
//' - "`5`" is "ECI mode".
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

static FILE *openFile(const char *outfile) {
  FILE *fp;

  if(outfile == NULL || (outfile[0] == '-' && outfile[1] == '\0')) {
    fp = stdout;
  } else {
    fp = fopen(outfile, "wb");
    if (fp == NULL) return(NULL);
  }

  return fp;
}

static void writeSVG_writeRect(FILE *fp, int x, int y, int width, char* col, float opacity) {
  if(fg_color[3] != 255) {
    fprintf(fp, "\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" "\
              "fill=\"#%s\" fill-opacity=\"%f\" />\n",
              x, y, width, col, opacity );
  } else {
    fprintf(fp, "\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" "\
              "fill=\"#%s\" />\n",
              x, y, width, col );
  }
}

CharacterVector writeSVG(QRcode *qrcode, int margin, int size, int dpi) {

  FILE *fp;
  unsigned char *row, *p;
  int x, y, x0, pen;
  int symwidth, realwidth;
  float scale;
  char fg[7], bg[7];
  float fg_opacity;
  float bg_opacity;

  char fname[L_tmpnam];
  memset(fname, 0, L_tmpnam);
  strncpy(fname,"qrencoder-XXXXXX", 16);

  fp = openFile(mktemp(fname));

  if (fp == NULL) return(R_NilValue);

  scale = dpi * INCHES_PER_METER / 100.0;

  symwidth = qrcode->width + margin * 2;
  realwidth = symwidth * size;

  snprintf(fg, 7, "%02x%02x%02x", fg_color[0], fg_color[1],  fg_color[2]);
  snprintf(bg, 7, "%02x%02x%02x", bg_color[0], bg_color[1],  bg_color[2]);
  fg_opacity = (float)fg_color[3] / 255;
  bg_opacity = (float)bg_color[3] / 255;

  /* XML declaration */
  fputs( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n", fp );

  /* DTD
   No document type specified because "while a DTD is provided in [the SVG]
   specification, the use of DTDs for validating XML documents is known to be
   problematic. In particular, DTDs do not handle namespaces gracefully. It
   is *not* recommended that a DOCTYPE declaration be included in SVG
   documents."
   http://www.w3.org/TR/2003/REC-SVG11-20030114/intro.html#Namespace
   */

  /* Vanity remark */
  fprintf( fp, "<!-- Created with qrencode %s (http://fukuchi.org/works/qrencode/index.html.en) -->\n",
           QRcode_APIVersionString() );

  /* SVG code start */
  fprintf( fp, "<svg width=\"%0.2fcm\" height=\"%0.2fcm\" viewBox=\"0 0 %d %d\""\
             " preserveAspectRatio=\"none\" version=\"1.1\""                    \
             " xmlns=\"http://www.w3.org/2000/svg\">\n",
             realwidth / scale, realwidth / scale, symwidth, symwidth
  );

  /* Make named group */
  fputs( "\t<g id=\"QRcode\">\n", fp );

  /* Make solid background */
  if(bg_color[3] != 255) {
    fprintf(fp, "\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%s\" fill-opacity=\"%f\" />\n", symwidth, symwidth, bg, bg_opacity);
  } else {
    fprintf(fp, "\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%s\" />\n", symwidth, symwidth, bg);
  }

  /* Create new viewbox for QR data */
  fputs( "\t\t<g id=\"Pattern\">\n", fp);

  /* Write data */
  p = qrcode->data;
  for(y=0; y<qrcode->width; y++) {
    row = (p+(y*qrcode->width));

    if( !rle ) {
      /* no RLE */
      for(x=0; x<qrcode->width; x++) {
        if(*(row+x)&0x1) {
          writeSVG_writeRect(fp,	margin + x,
                             margin + y, 1,
                             fg, fg_opacity);
        }
      }
    } else {
      /* simple RLE */
      pen = 0;
      x0  = 0;
      for(x=0; x<qrcode->width; x++) {
        if( !pen ) {
          pen = *(row+x)&0x1;
          x0 = x;
        } else {
          if(!(*(row+x)&0x1)) {
            writeSVG_writeRect(fp, x0 + margin, y + margin, x-x0, fg, fg_opacity);
            pen = 0;
          }
        }
      }
      if( pen ) {
        writeSVG_writeRect(fp, x0 + margin, y + margin, qrcode->width - x0, fg, fg_opacity);
      }
    }
  }
  /* Close QR data viewbox */
  fputs( "\t\t</g>\n", fp );

  /* Close group */
  fputs( "\t</g>\n", fp );

  /* Close SVG code */
  fputs( "</svg>\n", fp );
  fclose( fp );

  std::ifstream t(fname);
  std::string str((std::istreambuf_iterator<char>(t)),
                  std::istreambuf_iterator<char>());

  t.close();

  unlink(fname);

  return(Rcpp::wrap(str));

}

//' @md
//' @title Return a QR encoded string as an svg string
//' @description Encodes a string as a QR coder
//' @param to_encode character string to encode
//' @param version version of the symbol. If `0`, the library chooses the
//'        minimum version for the given input data.
//' @param level error correction level (`0` - `3`, lowest to highest)
//' @param hint tell the library how Japanese Kanji characters should be
//'        encoded:
//' - If "`3`", the library assumes that the given string contains Shift-JIS characters
//'   and encodes them in Kanji-mode.
//' - If "`2`" is given, all of non-alphanumerical characters will be encoded as is.
//'   If you want to embed UTF-8 string, choose this. Trying to encode UTF-8 with modes will cause an error.
//' - "`0`" is "numeric mode",
//' - "`1" is "alphanumeric mode"
//' - "`5`" is "ECI mode".
//' @param caseinsensitive case-sensitive(`1`) or not(`0`).
//' @param margin width of the marginsl default is 4
//' @param size  module size in dots (pixels); default is 3
//' @param dpi resolution; default = 72
//' @seealso \url{http://www.qrcode.com/en/about/version.html}
//' @export
// [[Rcpp::export]]
CharacterVector qrencode_svg(
    std::string to_encode,
    int version=0, int level=0, int hint=2,
    int caseinsensitive=1, int margin = 0, int size = 3, int dpi = 72) {

  QRcode *qrcode ;

  qrcode = QRcode_encodeString(to_encode.c_str(),
                               version,
                               (QRecLevel)level,
                               (QRencodeMode)hint, caseinsensitive);
  return(writeSVG(qrcode, margin, size, dpi));
}
