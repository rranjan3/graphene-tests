# Build Static as follows:
#
# - make               -- create non-SGX no-debug-log manifest
# - make DEBUG=1       -- create non-SGX debug-log manifest
# - make SGX=1         -- create SGX no-debug-log manifest
# - make SGX=1 DEBUG=1 -- create SGX debug-log manifest
#
# Any of these invocations clones Static git repository and builds it
# in the latest (master branch) version.
#
# Use `make clean` to remove Graphene-generated files and `make distclean` to
# additionally remove the cloned Static git repository.

################################# CONSTANTS ###################################

# Relative path to Graphene root
GRAPHENEDIR = ../../../../..

SRCDIR = src

ifeq ($(DEBUG),1)
GRAPHENEDEBUG = inline
else
GRAPHENEDEBUG = none
endif


.PHONY: all
all: static static.manifest pal_loader
ifeq ($(SGX),1)
all: static.manifest.sgx
endif

############################ STATIC EXECUTABLE ###############################

# Static is built as usual, without any changes to the build process. The
# source is built via a classic make. The result of this build process is
# the final executable "src/static".

$(SRCDIR)/static:
	cd $(SRCDIR) && make

############################## STATIC MANIFEST ###############################

# The template file contains almost all necessary information to run Static
# under Graphene / Graphene-SGX. We create static.manifest (to be run under
# non-SGX Graphene) by simply replacing variables in the template file via sed.

static.manifest: static.manifest.template
	sed -e 's|$$(GRAPHENEDIR)|'"$(GRAPHENEDIR)"'|g' \
		-e 's|$$(GRAPHENEDEBUG)|'"$(GRAPHENEDEBUG)"'|g' \
		$< > $@

# Manifest for Graphene-SGX requires special "pal-sgx-sign" procedure. This
# procedure measures all Static dependencies (shared libraries and trusted
# files), measures Static code/data pages, and adds measurements into the
# resulting manifest.sgx file (among other, less important SGX options).
#
# Additionally, Graphene-SGX requires EINITTOKEN and SIGSTRUCT objects (see
# SGX hardware ABI, in particular EINIT instruction). The "pal-sgx-get-token"
# script generates these objects and puts them in files .token and .sig
# respectively. Note that filenames must be the same as the executable/manifest
# name (i.e., "static").

static.manifest.sgx: static.manifest static
	$(GRAPHENEDIR)/Pal/src/host/Linux-SGX/signer/pal-sgx-sign \
		-libpal $(GRAPHENEDIR)/Runtime/libpal-Linux-SGX.so \
		-key $(GRAPHENEDIR)/Pal/src/host/Linux-SGX/signer/enclave-key.pem \
		-manifest $< -output $@ \
		-exec static
	$(GRAPHENEDIR)/Pal/src/host/Linux-SGX/signer/pal-sgx-get-token \
		-output static.token -sig static.sig

########################### COPIES OF EXECUTABLES #############################

# Static build process creates the final executable as "src/static".
# Copy Static binary to our root directory and create a link to pal_loader for
# simplicity.

static: $(SRCDIR)/static
	cp $(SRCDIR)/static static

pal_loader:
	ln -s $(GRAPHENEDIR)/Runtime/pal_loader $@

################################## CLEANUP ####################################

.PHONY: clean
clean:
	$(RM) *.token *.sig *.manifest.sgx *.manifest pal_loader static

distclean: clean
	cd $(SRCDIR) && make clean
