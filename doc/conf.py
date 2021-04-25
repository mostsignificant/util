# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

# -- Project information -----------------------------------------------------

import textwrap
import sphinx_rtd_theme

project = 'util'
copyright = '2020-2021, Christian Göhring'
author = 'Christian Göhring'

# The full version, including alpha/beta/rc tags
release = '2020'

# -- General configuration ---------------------------------------------------

extensions = [
    'breathe',
    'exhale'
]

templates_path = ['_templates']

exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'

html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

html_static_path = ['_static']

# -- Breathe configuration ---------------------------------------------------

breathe_projects = {
    "util": "./doxyoutput/xml"
}

breathe_default_project = "util"

# -- Exhale configuration ----------------------------------------------------

exhale_args = {
    "containmentFolder":     "./api",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "Library API",
    "doxygenStripFromPath":  "..",
    "createTreeView":        True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": textwrap.dedent('''
        INPUT      = ../include
        EXAMPLE_PATH = ../test"
    ''')
}

# -- Language configuration --------------------------------------------------

primary_domain = 'cpp'

highlight_language = 'cpp'
