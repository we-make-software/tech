github:
	git add .
	git commit -m "Auto-commit $(shell date '+%Y-%m-%d %H:%M:%S')"
	git push origin main
