# RapidXml

[![Build Status](https://travis-ci.org/timniederhausen/rapidxml.svg?branch=master)](https://travis-ci.org/timniederhausen/rapidxml)

This is a fork of Marcin Kalicinski's RapidXml library.

## Changes

* Some changes to the code to make it compile under newer compilers.
* CMake build scripts have been added.
* xml_base::offset() has been added (useful for generating diagnostics,
  that include the line/column inside the XML file).

## Documentation

The manual can be found at http://timniederhausen.github.io/rapidxml/,
or inside the `gh-pages` branch.

If you want to generate the documentation yourself, see
`doc/documentation/build_docs.bat`.

## License

Please see [license.txt](license.txt).
