
#include <Rcpp.h>

#include "farmhash.h"

//' Compute a 'FarmHash' digest for a vector of strings
//'
//' @param sv Vector of strings for which a hash digest is requested
//' @return A vector of \code{integer64} values (using the \pkg{bit64}
//' package to \sQuote{decode} the appropriate binary payload from a numeric
//' vector).
//' @examples
//' if (requireNamespace("bit64", quietly=TRUE)) {
//'    suppressMessages(library(bit64))
//' }
//' farmhash(c("foo", "bar", "baz"))
// [[Rcpp::export]]
Rcpp::NumericVector farmhash(const std::vector<std::string> & sv) {
    size_t n = sv.size();
    std::vector<int64_t> iv(n);

    for (size_t i=0; i<n; i++) {
        iv[i] = static_cast<int64_t>(util::Hash(sv[i].c_str(), sv[i].size()));
    }

    // see e.g. https://gallery.rcpp.org/articles/creating-integer64-and-nanotime-vectors/
    Rcpp::NumericVector nv(n);
    std::memcpy(&(nv[0]), &(iv[0]), n * sizeof(double));
    nv.attr("class") = "integer64";

    return nv;
}
