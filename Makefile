VERSION = 0.1
DATE = $(shell DATE)
UGLIFY_JS ?= `which uglifyjs`
CLEAN_CSS ?= `which cleancss`
BASE ?= ineo
NAME ?= ""

build:
	@@if test ! -z ${NAME}; then \
		cp -R ${BASE} ${NAME} && cd ${NAME}; \
		find . -type f | xargs sed -i .tmp 's/${BASE}/${NAME}/g'; \
		find . -type f -name \*.tmp | xargs rm; \
		for file in `find . -name '${BASE}.*'`; do \
			mv $$file `echo $$file | sed s/${BASE}/${NAME}/`; \
		done; \
		cd .. && mv ${NAME} ../${NAME}; \
		echo "Theme ${NAME} successfully built!"; \
	else \
		echo "Please provide a new theme name"; \
		echo "Run: make NAME=\"newthemename\""; \
	fi

js/min:
	@@if test ! -z ${UGLIFY_JS}; then \
		mkdir -p js/min; \
		uglifyjs -o js/min/ineo.min.js  js/ineo.js; \
		echo "JS files successfully minified!"; \
	else \
		echo "You must have the UGLIFY-JS minifier installed in order to minify Ineo's JS."; \
		echo "You can install it by running: npm install -g uglify-js"; \
	fi

css/min:
	@@if test ! -z ${CLEAN_CSS}; then \
		mkdir -p css/min; \
		cleancss -o css/min/ineo.min.css  css/ineo.css; \
		echo "CSS files successfully minified!"; \
	else \
		echo "You must have the CLEAN-CSS minifier installed in order to minify Ineo's CSS."; \
		echo "You can install it by running: npm install -g clean-css"; \
	fi

.PHONY: build
