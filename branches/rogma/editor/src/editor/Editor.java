package editor;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.gef.DefaultEditDomain;
import org.eclipse.gef.ui.parts.GraphicalEditor;

/**
 * Basic class for editor, probably the view 
 * 
 * @author mroger
 * 
 */
public class Editor extends GraphicalEditor
{

    public static final String ID = "pu.editor";

    public Editor()
    {
	setEditDomain(new DefaultEditDomain(this));
    }

    @Override
    protected void initializeGraphicalViewer()
    {
	// TODO Auto-generated method stub

    }

    @Override
    public void doSave(IProgressMonitor monitor)
    {
	// TODO Auto-generated method stub

    }

}
