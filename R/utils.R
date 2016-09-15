# appropriate from the RSAGA pkg with :heart:

to_xyz <- function (data, header, varname = "z", colnames = c("x", "y", varname)) {

  header <- list(ncols = ncol(data),
                 nrows = nrow(data),
                 xllcenter = 0, yllcenter = 0,
                 cellsize = 1, xllcorner = -0.5,
                 yllcorner = -0.5)

  data <- data.frame(x = header$xllcenter +
                       rep(seq(0, (header$ncols - 1) * header$cellsize, by = header$cellsize),
                           header$nrows),
                     y = rep(header$yllcenter +
                               seq((header$nrows - 1) * header$cellsize,
                                   0, by = -header$cellsize), each = header$ncols),
                     z = as.vector(t(data)))

  colnames(data) = colnames

  data

}
