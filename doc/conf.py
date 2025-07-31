# Configuration file for the Sphinx documentation builder.

import os
import sys

# -- Project information -----------------------------------------------------

project = 'Hermes'
author = 'Onur Tuncer, PhD'
copyright = '2025, Onur Tuncer, PhD'

# -- General configuration ---------------------------------------------------

extensions = [
    'breathe',
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.graphviz',
    'sphinx.ext.intersphinx',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx.ext.githubpages',
    'sphinxcontrib.bibtex',
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

# -- Breathe configuration ---------------------------------------------------

# Absolute path to doxygen XML output (from CMake)
# CMake should place it at: build/doc/doxygen/xml
breathe_projects = {
    "Hermes": os.path.abspath(os.path.join(os.path.dirname(__file__), "doxygen/xml"))
}
breathe_default_project = "Hermes"
breathe_default_namespace = "Hermes"

# Whether to add '()' to function entries in the index and elsewhere
add_function_parentheses = True

# Optional: helpful print for debugging
print("Breathe expects Doxygen XML at:", breathe_projects["Hermes"])

# -- BibTeX references -------------------------------------------------------

bibtex_bibfiles = ['references.bib']
bibtex_encoding = 'latin'

# -- ReadTheDocs fallback (optional) -----------------------------------------

read_the_docs_build = os.environ.get('READTHEDOCS') == 'True'

if read_the_docs_build:
    # On ReadTheDocs, we need to generate Doxygen ourselves
    import subprocess

    doxygen_output_dir = 'build/xml'
    doxygen_input_dir = '../src'

    with open('Doxyfile.in', 'r') as file:
        doxy_config = file.read()
    doxy_config = doxy_config.replace('@DOXYGEN_INPUT_DIR@', doxygen_input_dir)
    doxy_config = doxy_config.replace('@DOXYGEN_OUTPUT_DIR@', doxygen_output_dir)
    with open('Doxyfile', 'w') as file:
        file.write(doxy_config)

    subprocess.call('doxygen', shell=True)
    breathe_projects['Hermes'] = os.path.abspath(os.path.join(os.path.dirname(__file__), 'build/xml'))
