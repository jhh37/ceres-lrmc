/*
 * Ceres on E(U,V)
 * Je Hyeong Hong
 */

#include "_everyheader.h"
#include "glog/logging.h"

/*
 *  (FUNCTION) main: Parse the argument and pass it on to the runExperiment function.
 */
int main(int argc, char* argv[]) {

  // Initialise google log.
  google::InitGoogleLogging(argv[0]);

  // Declare experiment options variable.
  options_t opts;
  
  // Parse experiment options from input arguments.
  parseOptionsFromArgs(argc, argv, opts);

  // If user has not called for help, run the experiment.
  if (!opts.help) {
    runExperiment(opts);
  }

	return 0;
}
