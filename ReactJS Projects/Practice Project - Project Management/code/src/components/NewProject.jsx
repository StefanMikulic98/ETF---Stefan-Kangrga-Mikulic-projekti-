import Input from './Input.jsx';
import Modal from './Modal.jsx';
import { useRef } from 'react';

export default function NewProject({ onSelectCancel, onSelectSave }) {
    const titleInput = useRef();
    const descriptionInput = useRef();
    const dateInput = useRef();
    const modal = useRef();   

    function handleChange() {
        const enteredTitle = titleInput.current.value;
        const enteredDescription = descriptionInput.current.value;
        const enteredDate = dateInput.current.value;             

        if (enteredTitle.trim() === '' || enteredDescription.trim() === '' || enteredDate.trim() === '') {
            modal.current.open();
            return;
        }

        const newProject = {
            title: enteredTitle,
            description: enteredDescription,
            date: enteredDate
        };

        onSelectSave(newProject);
        
    }
    
    return (
        <>
            <Modal ref={modal} buttonCaption="Okay" >
                <h2 className="text-xl font-bold text-stone-700 my-4">Invalid Input</h2>
                <p className="text-stone-600 mb-4">
                    Oops ... looks like you forgot to enter a value.
                </p>
                <p className="text-stone-600 mb-4">
                    Please make sure you provide a valid value for every input field.
                </p>
            </Modal>
            <div className="w-[35rem] mt-16">
                <menu className="flex items-center justify-end gap-4 my-4">
                    <button className="text-stone-700 hover:text-stone-950" onClick={onSelectCancel}>
                        Cancel
                    </button>
                    <button className="px-6 py-2 rounded-md bg-stone-800 text-stone-50 hover:bg-stone-950" onClick={handleChange}>
                        Save
                    </button>
                </menu>
                <div>
                    <Input ref={titleInput} type="text" label="title" />
                    <Input ref={descriptionInput} label="description" isTextArea />
                    <Input ref={dateInput} type="date" label="due date" />
                </div>
            </div>
        </>
    );
}
