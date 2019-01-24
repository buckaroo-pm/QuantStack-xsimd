load('//:subdir_glob.bzl', 'subdir_glob')

prebuilt_cxx_library(
  name = 'xsimd',
  header_only = True,
  header_namespace = '',
  exported_headers = subdir_glob([
    ('include', '**/*.hpp'),
  ]),
  visibility = [
    'PUBLIC',
  ],
)
