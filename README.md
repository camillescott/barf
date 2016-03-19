# barf
## drop-in bioinformatics validation

To try it out, first clone the repository:

    git clone https://github.com/camillescott/barf.git

The software isn't properly package yet. So, move into the inner barf folder:

    cd barf/barf

There are python dependencies. First, create a new virtualenv:

    virtualenv venv

If you don't have virtualenv, it can be installed through aptitude like so:

    sudo apt-get install virtualenv

And activate it:
    
    . venv/bin/activate

Now install the dependencies:

    pip install screed pybloom


Now we can run the tests like so:

    make badfasta
    make extrarecord
