#include <iostream>
#include <cmath>

#include "parser.h"

void parseOptionsFromArgs(int argc, char* argv[], options_t &options) {
  
  // If no arguments provided, check for help and then allow user to type them one by one.
  if (argc < 2) {
    
    parseOptionsManually(options, 1);
    
    // Otherwise, parse the input arguments.
  } else {
    
    std::string arg;
    std::string argType;
    int len = 0;
    
    for (int i = 1; i < argc; i++) {
      
      arg = argv[i];
      len = int(arg.find('='));
      argType = arg.substr(0, len);
      arg = arg.substr(len + 1);
      
      // Parse dataset.
      if (argType == "-d" || argType == "--dataset") {
        options.dataset = arg;
      } else if (argType == "-p" || argType == "--path") {
        options.path = arg;
        // Parse the number of rows.
      } else if (argType == "-m" || argType == "--num_rows") {
        options.num_rows = atoi(arg.c_str());
        // Parse the number of columns.
      } else if (argType == "-n" || argType == "--num_cols") {
        options.num_cols = atoi(arg.c_str());
        // Parse rank.
      } else if (argType == "-r" || argType == "--rank") {
        options.rank = atoi(arg.c_str());
        // Parse tolerance.
      } else if (argType == "-t" || argType == "--func_tol") {
        options.func_tol = std::strtod(arg.c_str(), NULL);
        // Parse the maximum number of iterations.
      } else if (argType == "-i" || argType == "--max_num_iterations") {
        options.max_num_iterations = atoi(arg.c_str());
        // Parse the number of threads used.
      } else if (argType == "--num_threads") {
        options.num_threads = atoi(arg.c_str());
        // Parse the square root of the regularization parameter.
      } else if (argType == "--nu") {
        // If PCA formulation is used, then set nu to 0.
        if (options.use_pca) {
          options.sqrt_nu = 0.0;
          
          // Otherewise, do the maths.
        } else {
          options.sqrt_nu = sqrt(std::strtod(arg.c_str(), NULL));
        }

        // Parse whether to use Jacobi scaling in CERES.
      } else if (argType == "--use_jacobi_scaling") {
        options.use_jacobi_scaling = atoi(arg.c_str()) > 0 || (arg == argType);
        
        // Parse whether to use inner iterations in CERES.
      } else if (argType == "--use_inner_iterations") {
        options.use_inner_iterations = atoi(arg.c_str()) > 0 || (arg == argType);
        
        // Parse whether to use automatic derivatives in CERES.
      } else if (argType == "--use_auto_differentiation") {
        options.use_auto_differentiation = atoi(arg.c_str()) > 0 || (arg == argType);
        
        // Parse whether to eliminate U first or not
      } else if (argType == "--eliminate_u_first") {
        options.eliminate_u_first = atoi(arg.c_str()) > 0 || (arg == argType);
        
        // Use Levenberg damping: lambda * eye(size(JTJ).
      } else if (argType == "--use_levenberg_damping") {
        options.use_levenberg_damping =
            atoi(arg.c_str()) > 0 || (arg == argType);
        // Use Traditional damping update.
      } else if (argType == "--use_traditional_damping_update") {
        options.use_traditional_damping_update =
            atoi(arg.c_str()) > 0 || (arg == argType);
        // Use RW2 as the inner iteration strategy.
      } else if (argType == "--use_rw2_for_inner_iterations") {
        options.use_rw2_for_inner_iterations =
            atoi(arg.c_str()) > 0 || (arg == argType);
        // Use linear RW2/EMP.
      } else if (argType == "--use_linear_inner_iterations") {
        options.use_linear_inner_iterations =
            atoi(arg.c_str()) > 0 || (arg == argType);
        // Perform inner iterations on V only.
      } else if (argType == "--use_inner_iterations_for_v_only") {
        options.use_inner_iterations_for_v_only =
            atoi(arg.c_str()) > 0 || (arg == argType);
        // Use Block QR factorization for RW2.
      } else if (argType == "--use_block_qr_for_rw2") {
        options.use_block_qr_for_rw2 =
            atoi(arg.c_str()) > 0 || (arg == argType);
        // Initialize with inner iteration.
      } else if (argType == "--initialize_with_inner_iteration") {
        options.initialize_with_inner_iteration =
            atoi(arg.c_str()) > 0 || (arg == argType);
      // Parse whether to use PCA formulation.
      } else if (argType == "--use_pca") {
        options.use_pca = atoi(arg.c_str()) > 0 || (arg == argType);
        
        // If PCA is used, force the regularization parameter to be 0.
        if (options.use_pca) { options.sqrt_nu = 0.0; }
        
        // Parse whether to display the outputs.
      } else if (argType == "--display") {
        options.display = atoi(arg.c_str()) > 0 || (arg == argType);
        
        // Parse whether to output debug infos.
      } else if (argType == "--debug") {
        options.debug =  atoi(arg.c_str()) > 0 || (arg == argType);
        
        // Output a list of commands.
      } else if (argType == "/?" || argType == "-h" || argType == "--help") {
        options.help = true;
        outputCommands();
        return;
      }
    } // End of for loop
    
    // Parse options manually for incorrect inputs.
    parseOptionsManually(options, 0);
    
    // If debug is on, output the input arguments.
    if (options.debug) {
      
      std::cout << std::endl;
      
      std::cout << "---[ PARSED INPUT ARGUMENTS ]---" << std::endl;
      
      std::cout << "1. Dataset: " << options.dataset << std::endl;
      std::cout << "2. Path: " << options.path << std::endl;
      std::cout << "3. Size: " << options.num_rows << " x " << options.num_cols << std::endl;
      std::cout << "4. Rank: " << options.rank << std::endl;
      std::cout << "5. Function tolerance: " << options.func_tol << std::endl;
      std::cout << "6. Max. no. of evaluations: " << options.max_num_iterations << std::endl;
      std::cout << "7. Number of threads: " << options.num_threads << std::endl << std::endl;
      std::cout << "8. Sqrt(nu) = " << options.sqrt_nu << std::endl << std::endl;
      std::cout << "9. use_inner_iterations: " << options.use_inner_iterations << std::endl;
      std::cout << "10. use_auto_differentiation: " << options.use_auto_differentiation << std::endl;
      std::cout << "11. use_pca: " << options.use_pca << std::endl;
      std::cout << "12. eliminate_u_first: " << options.eliminate_u_first << std::endl;
      std::cout << "13. use_levenberg_damping: " << options.use_levenberg_damping << std::endl;
      std::cout << "14. use_traditional_damping_update: " << options.use_traditional_damping_update << std::endl;
      std::cout << "15. use_rw2_for_inner_iterations: " << options.use_rw2_for_inner_iterations << std::endl;
      std::cout << "16. use_linear_inner_iterations: " << options.use_linear_inner_iterations << std::endl;
      std::cout << "17. use_inner_iterations_for_v_only: " << options.use_inner_iterations_for_v_only << std::endl;
      std::cout << "18. use_block_qr_for_rw2: " << options.use_block_qr_for_rw2 << std::endl;
      std::cout << "19. initialize_with_inner_iteration: " << options.initialize_with_inner_iteration << std::endl;
      std::cout << "20. display: " << options.display << std::endl;
      
      std::cout << std::endl;
      
    }
  }
  
  return;
}

void parseOptionsManually(options_t &options, bool START_FROM_SCRATCH) {
  
  // If starting from scratch, reset the options to default.
  if (START_FROM_SCRATCH) { options.reset(); }
  
  while (options.dataset.length() < 1) {
    std::cout << "Please enter the dataset name: ";
    std::cin >> options.dataset;
  }
  
  while (options.num_rows < 1) {
    std::cout << "Please enter the number of rows (m): ";
    std::cin >> options.num_rows;
  }
  
  while (options.num_cols < 1) {
    std::cout << "Please enter the number of columns (n): ";
    std::cin >> options.num_cols;
  }
  
  while (options.rank < 1) {
    std::cout << "Please enter the proposed rank (r): ";
    std::cin >> options.rank;
  }
  
  // Only type again the followings if starting from scratch.
  //  if (START_FROM_SCRATCH) {
  //    std::cout << "Please specify the tolerance threshold (default = 1e-10): ";
  //    std::cin >> options.func_tol;
  //
  //    std::cout << "Please specify the iteration threshold (default = 2000): ";
  //    std::cin >> options.num_rowsax_iter;
  //
  //    std::cout << "Please enter the number of CPUs to be used (default = 1): ";
  //    std::cin >> options.num_procs;
  //
  //    std::cout << "Please enter the proposed value of the square root of the regularization parameter (sqrt_nu | default = 0.0): ";
  //    std::cin >> options.sqrt_nu;
  //
  //    std::cout << "Please specify whether to use inner iterations (1 = on, 0 = off | default = 0): ";
  //    std::cin >> options.USE_inner_iterations;
  //
  //    std::cout << "Please specify whether to use automatic derivatives (1 = on, 0 = off | default = 0): ";
  //    std::cin >> options.USE_auto_differentation;
  //
  //    std::cout << "Please specify whether to use PCA-mode (1 = on, 0 = off | default = 0): ";
  //    std::cin >> options.USE_PCA;
  //    std::cout << std::endl;
  //
  //    std::cout << "Please specify whether to eliminate U first (1 = U first, 0 = V first | default = 0): ";
  //    std::cin >> options.ELIMINATE_U_FIRST;
  //    std::cout << std::endl;
  //  }
  
  return;
}

void outputCommands() {
  
  std::cout << std::endl;
  
  std::cout << "--- [ LIST OF COMMANDS ] ---" << std::endl << std::endl;
  
  std::cout << "[ Dataset-related ]" << std::endl;
  std::cout << "-d=<string>, --dataset=<string>: Read dataset from <name>_r<rank>_{M, W, U0, V0}.bin." << std::endl;
  std::cout << "-p=<string>, --path=<string>: Set the path." << std::endl;
  std::cout << "-m=<int>, --num_rows=<int>: Set the number of rows." << std::endl;
  std::cout << "-n=<int>, --num_cols=<int>: Set the number of columns." << std::endl;
  std::cout << "-r=<int>, --rank=<int>: Set the proposed rank." << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "[ Solver-related ]" << std::endl;
  std::cout << "-t=<double>, --func_tol=<double>: Set the function tolerance. (default = 1e-10)" << std::endl;
  std::cout << "-i=<int>, --max_num_iterations=<double>: Set the maximum number of iterations. (default = 2000)" << std::endl;
  std::cout << "--nu=<double>: Set regularization parameter nu. (default = 0.0)" << std::endl;
  std::cout << "--num_threads=<double>: Set the number of threads for the solver. (default = 1)" << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "--use_inner_iterations[=<bool>]: Specify whether to use inner iterations or not. (default = 0)" << std::endl;
  std::cout << "--use_auto_differentation[=<bool>]: Specify whether to use automatic derivatives or not. (default = 0)" << std::endl;
  std::cout << "--use_pca[=<bool>]: Specify whether to use PCA formulation or not. (default = 0)" << std::endl;
  std::cout << "--eliminate_u_first[=<bool>]: Specify whether to eliminate U first or V first. (default = 0)" << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "[ Program-related ]" << std::endl;
  std::cout << "--display[=<bool>]: Specify whether to show progress in detail. (default = 1)" << std::endl;
  std::cout << "--debug[=<bool>]: Specify whether to show debug-related information. (default = 0)" << std::endl;
  
  std::cout << std::endl;
  
  std::cout << "[ Miscellaneous]" << std::endl;
  std::cout << "/?, -h, --help: Show a list of available commands." << std::endl;
  
  std::cout << std::endl;
  
  return;
}