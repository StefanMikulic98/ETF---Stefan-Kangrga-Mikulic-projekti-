export default function Input({ label, id, error , ...props }) {
    return (
        <>
            <label htmlFor={id}>{label}</label>
            <input id={id} {...props} />  
            {error && <p className ="error">{error}</p>}           
        </>
    );
}
