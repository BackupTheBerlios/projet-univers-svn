package editor;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IPersistableElement;

/**
 * Probably the main controler class 
 * @author mroger
 *
 */
public class EditorControler implements IEditorInput
{

    public EditorControler(String name)
    {
	this.name = name ;
    }
    
    @Override
    public Object getAdapter(Class adapter)
    {
	// TODO Auto-generated method stub
	return null;
    }

    @Override
    public boolean exists()
    {
	return name != null;
    }

    @Override
    public ImageDescriptor getImageDescriptor()
    {
	return ImageDescriptor.getMissingImageDescriptor();
    }

    @Override
    public String getName()
    {
	return name;
    }

    @Override
    public IPersistableElement getPersistable()
    {
	// TODO Auto-generated method stub
	return null;
    }

    @Override
    public String getToolTipText()
    {
	return this.name;
    }

    public String name = null;
}
