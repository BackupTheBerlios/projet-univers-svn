package editor;

import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.application.IWorkbenchWindowConfigurer;
import org.eclipse.ui.application.WorkbenchAdvisor;
import org.eclipse.ui.application.WorkbenchWindowAdvisor;

public class ApplicationWorkbenchAdvisor extends WorkbenchAdvisor
{

    private static final String PERSPECTIVE_ID = "editor.perspective"; //$NON-NLS-1$

    public WorkbenchWindowAdvisor createWorkbenchWindowAdvisor(
	    IWorkbenchWindowConfigurer configurer)
    {
	return new ApplicationWorkbenchWindowAdvisor(configurer);
    }

    public String getInitialWindowPerspectiveId()
    {
	return PERSPECTIVE_ID;
    }

    @Override
    /// Main method.
    public void postStartup()
    {
	try
	{
	    IWorkbenchPage page = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
	    page.openEditor(new EditorControler("ProjetUnivers"),Editor.ID,false);
	}
	catch (Exception e)
	{
	    e.printStackTrace();
	}
    }
}
