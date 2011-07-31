package editor;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPartFactory;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;


public class ControlerFactory implements EditPartFactory
{

    @Override
    public EditPart createEditPart(EditPart context, Object model)
    {
        AbstractGraphicalEditPart part = null; 
        
	if (model instanceof editor.model.Object)
	{
	    part = new editor.controler.Object();
	}

	if (model instanceof editor.model.Model)
	{
	    part = new editor.controler.Model();
	}
	
        part.setModel(model);
        return part;
     }

}
