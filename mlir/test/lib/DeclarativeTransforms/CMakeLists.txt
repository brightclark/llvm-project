set(LLVM_TARGET_DEFINITIONS TestLinalgTransformPatterns.td)
mlir_tablegen(TestLinalgTransformPatterns.h.inc -gen-rewriters)
add_public_tablegen_target(MLIRTestLinalgTransformPatternsIncGen)
# Including Linalg in TableGen requires to depends on generated files
add_dependencies(MLIRTestLinalgTransformPatternsIncGen LinalgOdsGen)

set(LLVM_TARGET_DEFINITIONS TestVectorTransformPatterns.td)
mlir_tablegen(TestVectorTransformPatterns.h.inc -gen-rewriters)
add_public_tablegen_target(MLIRTestVectorTransformPatternsIncGen)
