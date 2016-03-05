all: project-proposal.pdf progress-report.pdf

project-proposal.pdf: project-proposal.md barf.bib
	pandoc -f markdown+fenced_code_blocks+fenced_code_attributes+tex_math_dollars+implicit_figures --bibliography barf.bib  --filter pandoc-citeproc $< -o $@

progress-report.pdf: progress-report.md barf.bib
	pandoc -f markdown+fenced_code_blocks+fenced_code_attributes+tex_math_dollars+implicit_figures --bibliography barf.bib  --filter pandoc-citeproc $< -o $@
