<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output encoding="utf-8" indent="yes"/>

	<xsl:template match="TestRun">
		<testsuite name=""
			tests="{normalize-space(Statistics/Tests)}"
			failures="{normalize-space(Statistics/Failures)}"
			errors="{normalize-space(Statistics/Errors)}" time="">
			<xsl:apply-templates/>
		</testsuite>
	</xsl:template>

	<xsl:template match="FailedTests">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="SuccessfulTests">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="Test">
		<testcase name="{normalize-space(Name)}" time="" />
	</xsl:template>

	<xsl:template match="FailedTest">
		<testcase name="{normalize-space(Name)}" time="">
			<failure message="{normalize-space(FailureType)}: {string(text()[last()])}">
			</failure>
		</testcase>
	</xsl:template>

	<xsl:template match="Statistics">
	</xsl:template>

</xsl:stylesheet>

